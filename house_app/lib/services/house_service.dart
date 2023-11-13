import 'dart:async';
import 'dart:convert';
import 'package:http/http.dart' as http;

Future<http.Response> getSelectedFilter(String filter) async {
  var url = "http://192.168.0.102:5001/home/get_selected_filter";

  final Map<String, String> data = {"filter": filter};

  var headers = {"Content-Type": "application/json"};

  var response = await http.post(
    Uri.parse(url),
    headers: headers,
    body: json.encode(data),
  );

  return response;
}

Future<http.Response> takePhoto() async {
  var url = "http://192.168.0.102:5001/home/take_photo";

  var headers = {"Content-Type": "application/json"};

  var response = await http.get(Uri.parse(url), headers: headers);

  return response;
}

Future<http.Response> applyPhotoFilter(String filter, int useOmp) async {
  var url = "http://192.168.0.102:5001/home/apply_filter";

  final Map<String, dynamic> data = {"filter": filter, "omp": useOmp};

  var headers = {"Content-Type": "application/json"};

  var response = await http.post(
    Uri.parse(url),
    headers: headers,
    body: json.encode(data),
  );

  return response;
}

Future<http.Response> getFilteredImage() async {
  var url = "http://192.168.0.102:5001/home/get_filtered_image";

  var headers = {"Content-Type": "application/json"};

  var response = await http.get(Uri.parse(url), headers: headers);

  return response;
}
