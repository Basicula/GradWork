import Pyro4
from flask import Flask, render_template, request, send_from_directory, jsonify, Response
import socket
import configparser
from .node import Node
from .node_link import create_node_link
from .file_utils import get_job_directory, OUTPUT_FILE_NAME, SOLUTION_FILE_NAME, INPUT_FILE_NAME, store_input, \
    store_solution, setup_working_directory
from .job import Job
import logging
from queue import Queue
from .network_utils import find_free_port, get_ip
from .scheduler import Scheduler


class Config:
    NODE_SECTION = 'Node'
    MASTER_NODE_SECTION = 'Master Node'

    def __init__(self, ip, port, master_ip=None, master_port=None):
        self.master = master_ip is None
        self.ip = ip if ip else get_ip()
        self.port = port if port else find_free_port()
        self.job_home = setup_working_directory()
        self.master_ip = master_ip
        self.master_port = master_port

    @staticmethod
    def load_from_file(config_path):
        configuration = configparser.ConfigParser()
        configuration.read(config_path)

        master = configuration.getboolean(Config.NODE_SECTION, 'master')
        ip = configuration.get(Config.NODE_SECTION, 'ip') if configuration.has_option(Config.NODE_SECTION,
                                                                                             'ip') else None
        port = configuration.getint(Config.NODE_SECTION, 'port') if configuration.has_option(Config.NODE_SECTION,
                                                                                             'port') else None

        if not master:
            master_ip = configuration.get(Config.MASTER_NODE_SECTION, 'ip')
            master_port = configuration.getint(Config.MASTER_NODE_SECTION, 'port')
            return Config(ip, port, master_ip, master_port)
        return Config(ip, port)


def start(conf):
    log.info("Starting...")
    app.node = Node.create_node(conf)
    if app.node.is_master_node():
        app.scheduler = Scheduler(app.node, app.scheduled_jobs)
        app.scheduler.start()
    log.info("Started.")
    app.run(host='0.0.0.0', port=conf.port)


logging.basicConfig(level=logging.INFO)

log = logging.getLogger('PARCS')

app = Flask(__name__)
app.debug = False
app.node = None
app.scheduler = None
app.scheduled_jobs = Queue()


def bad_request():
    return Response(status=400)


def not_found():
    return Response(status=404)


def ok():
    return Response(status=200)


# WEB
@app.route('/')
@app.route('/index')
def index_page():
    return render_template('index.html')

@app.route('/about')
def about_page():
    return render_template("about.html")

@app.route('/simulation', methods=['GET'])
def simulation():
    return render_template("simulation.html")

# Inernal api
@app.route('/api/internal/heartbeat')
def heartbeat():
    return ok()


@app.route('/api/internal/worker', methods=['POST'])
def register_worker():
    json = request.get_json()
    node_link = create_node_link(json)
    log.info("Worker %s is about to register.", str(node_link))
    result = app.node.register_worker(node_link)
    if result:
        log.info("Worker %s registered.", str(node_link))
        return jsonify(worker=node_link.serialize())
    else:
        return bad_request()
    
    
    
    
    
    
