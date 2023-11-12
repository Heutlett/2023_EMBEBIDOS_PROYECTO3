from flask import Flask
from flask import json, jsonify
from flask import request, send_file
from flask_cors import CORS

from config import server_config as sconf
from config.constants import *

from controllers import webcam
from controllers import filters


# Creating an basic app
app = Flask(__name__)
cors = CORS(app)
app.config['CORS_HEADERS'] = 'Content-Type'


@app.route('/', methods=['GET'])
def home():
    """
    This function returns a message for the basic API route.
    """
    return f'<h1>Image filter API</h1><p>Welcome to the API.</p>'


@app.route('/home/get_selected_filter', methods=['POST'])
def get_selected_filter():
    """
    This function is used to get a filter selected.
    """
    # Get params
    body = request.json
    filter = body['filter']

    # Generic response
    response = {
        'error': False,
        'data': None,
        'msg': None
    }

    # Check if the pin is valid
    if (filter not in PINS['filters']):
        response['error'] = True
        response['msg'] = '{filter} not found.'
    else:
        response['data'] = {
            'state': filters.get_state(filter)
        }

    return jsonify(response)


@app.route('/home/take_photo', methods=['GET'])
def take_photo():
    """
    This function is used to take a photo of a filter.
    """
    img_path = webcam.take_photo()

    return send_file(img_path)


if __name__ == '__main__':
    filters.start()
    app.run(host=sconf.HOST, port=sconf.PORT)

