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
        print("antes de filters.get_state(filter)")
        response['data'] = {
            'state': filters.get_state(filter)
        }

    return jsonify(response)

@app.route('/home/get_use_omp', methods=['POST'])
def get_use_omp():
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
    filters.take_photo_gst(INPUT_IMG_PATH)

    return send_file(INPUT_IMG_PATH)

@app.route('/home/apply_filter', methods=['POST'])
def apply_filter():
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
    
    if(filter == "filter1"):
        time_elapsed_no_omp = filters.apply_filter(input_path=INPUT_IMG_PATH, output_path=OUTPUT_IMG_PATH, filter=1, use_omp=0)
        time_elapsed_omp = filters.apply_filter(input_path=INPUT_IMG_PATH, output_path=OUTPUT_IMG_PATH, filter=1, use_omp=1)
    elif(filter == "filter2"):
        time_elapsed_no_omp = filters.apply_filter(input_path=INPUT_IMG_PATH, output_path=OUTPUT_IMG_PATH, filter=2, use_omp=0)
        time_elapsed_omp = filters.apply_filter(input_path=INPUT_IMG_PATH, output_path=OUTPUT_IMG_PATH, filter=2, use_omp=1)
    elif(filter == "filter3"):
        time_elapsed_no_omp = filters.apply_filter(input_path=INPUT_IMG_PATH, output_path=OUTPUT_IMG_PATH, filter=3, use_omp=0)
        time_elapsed_omp = filters.apply_filter(input_path=INPUT_IMG_PATH, output_path=OUTPUT_IMG_PATH, filter=3, use_omp=1)

    print('time_elapsed_no_omp: {:.2f}'.format(time_elapsed_no_omp))
    print('time_elapsed_omp: {:.2f}'.format( time_elapsed_omp))
    print('boosted for: {:.2f}'.format(time_elapsed_no_omp-time_elapsed_omp))
    
    response['data'] = {
        'time_elapsed_no_omp': time_elapsed_no_omp,
        'time_elapsed_omp': time_elapsed_omp
    }

    return jsonify(response)
    
@app.route('/home/get_filtered_image', methods=['GET'])
def get_filtered_image():
    """
    This function is used to take a photo of a filter.
    """

    return send_file(OUTPUT_IMG_PATH)

if __name__ == '__main__':
    filters.start()
    app.run(host=sconf.HOST, port=sconf.PORT)

