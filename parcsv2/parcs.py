import logging
import requests
import json
import os
import random
from flask import Flask, render_template, request, send_from_directory, jsonify, Response, make_response

from .node import Node
from .node_link import create_node_link

from engine import Scene
from engine.Visual import Image, Color
from engine.Visual.Material import ColorMaterial
from engine.Primitives import Sphere
from engine.Math.Vector import Vector3d

def start(conf):
    log.info("Starting...")
    app.node = Node.create_node(conf,"./parcsv2/Scenes")
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
    scenes_folder = os.walk(app.node.scenes_root)
    scenes = []
    for addr, dirs, files in scenes_folder:
        for file in files:
            if '.json' in file:
                scene = {}
                scene["name"] = file.split('.')[0]
                scene["file"] = file
                scenes.append(scene)
    return render_template('index.html', scenes = scenes)

@app.route('/about')
def about_page():
    return render_template("about.html")

@app.route('/simulation/<filename>', methods=['GET'])
def simulation(filename):
    for worker in app.node.workers:
        response = requests.post(('http://%s:%s/api/internal/worker/scene/init/' + filename) % (worker.ip, worker.port))
    return render_template("simulation.html")
    
@app.route('/simulation/update', methods=['GET'])
def simulation_update():
    response = None
    for worker in app.node.workers:
        response = requests.get('http://%s:%s/api/internal/worker/scene/update' % (worker.ip, worker.port))
    return response.json()

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
        
@app.route('/api/internal/worker/scene/init/<filename>', methods = ['POST'])
def scene_init(filename):
    scenes_folder = os.walk(app.node.scenes_root)
    scenes = []
    for addr, dirs, files in scenes_folder:
        for file in files:
            if filename in file:
                with open(addr+'/'+file,'r') as f:
                    app.node.scene = Scene.fromDict(json.load(f))
    app.image = Image(app.node.scene.frameWidth, app.node.scene.frameHeight)
    return ok()
    
@app.route('/api/internal/worker/scene/update', methods = ['GET'])
def scene_update():
    width = app.node.scene.frameWidth
    height = app.node.scene.frameHeight
    x = random.uniform(-20, 20)
    y = random.uniform(-20, 20)
    z = random.uniform(-10, 0)
    app.node.scene.addObject(
        Sphere(
            Vector3d(x,y,z),
            2,
            ColorMaterial(Color(random.randint(0,0xffffff)))))
    app.node.scene.getFrame(app.image)
    return json.dumps({"image":str(app.image), "width" : width, "height" : height})