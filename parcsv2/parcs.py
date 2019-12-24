import logging
import requests
import json
from flask import Flask, render_template, request, send_from_directory, jsonify, Response

from .node import Node
from .node_link import create_node_link

def start(conf):
    log.info("Starting...")
    app.node = Node.create_node(conf)
    log.info("Started.")
    app.run(host='0.0.0.0', port=conf.port)
    app.inited = False

logging.basicConfig(level=logging.INFO)

log = logging.getLogger('PARCS')

app = Flask(__name__)
app.debug = False
app.node = None
app.inited = False

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
    
@app.route('/test', methods=['GET'])
def test():
    values = []
    for worker in app.node.workers:
        if not app.inited:
            response = requests.get('http://%s:%s/api/internal/test/init/0' % (worker.ip, worker.port))
            values.append(0)
        else:
            response = requests.get('http://%s:%s/api/internal/test' % (worker.ip, worker.port))
            values.append(response.content)
    app.inited = True
    return render_template("test.html", workers = app.node.workers, values = values)

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

@app.route('/api/internal/test/init/<num>', methods=['GET'])
def internal_test_init(num):
    app.node.init(int(num))
    return ok()
    
@app.route('/api/internal/test', methods=['GET'])
def internal_test():
    if app.node.is_master_node():
        resp = {}
        resp["data"] = []
        for worker in app.node.workers:
            w = {}
            w["ip"] = worker.ip
            w["port"] = worker.port
            response = requests.get('http://%s:%s/api/internal/test' % (worker.ip, worker.port))
            w["val"] = json.loads(response.content)
            resp["data"].append(w)
        return resp
    else:
        val = app.node.get()
        return str(val)