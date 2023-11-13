import 'dart:async';
import 'dart:convert';

import 'package:flutter/material.dart';
import 'package:house_app/services/house_service.dart';

class DiagramScreen extends StatefulWidget {
  DiagramScreen({super.key});
  List<int> selectedFilters = [0, 0, 0];
  int useOmp = 0;
  double timeElapsedNoOmp = 0;
  double timeElapsedOmp = 0;

  @override
  State<DiagramScreen> createState() => _DiagramScreenState();
}

class _DiagramScreenState extends State<DiagramScreen> {
  @override
  void initState() {
    super.initState();

    // Utiliza un Timer.periodic para obtener el estado del LED cada 2 segundos.
    Timer.periodic(const Duration(seconds: 2), (timer) {
      getSelectedFilter('filter1').then((response) {
        setState(() {
          widget.selectedFilters[0] =
              jsonDecode(response.body)['data']['state'];
        });
      }).catchError((error) {});

      getSelectedFilter('filter2').then((response) {
        setState(() {
          widget.selectedFilters[1] =
              jsonDecode(response.body)['data']['state'];
        });
      }).catchError((error) {});

      getSelectedFilter('filter3').then((response) {
        setState(() {
          widget.selectedFilters[2] =
              jsonDecode(response.body)['data']['state'];
        });
      }).catchError((error) {});

      getSelectedFilter('omp').then((response) {
        setState(() {
          widget.useOmp = jsonDecode(response.body)['data']['state'];
        });
      }).catchError((error) {});
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Container(
        color: const Color.fromARGB(255, 8, 45, 82),
        child: Column(
          mainAxisAlignment: MainAxisAlignment.start,
          children: [
            const SizedBox(height: 100),
            const Text(
              'Raspberry Pi 2 - Photo Filter System with Yocto',
              style: TextStyle(fontSize: 45, color: Colors.white),
            ),
            const SizedBox(height: 200),
            GestureDetector(
              onTap: () {
                _takePhoto();
              },
              child: Center(
                child: Container(
                  width: 530,
                  height: 100,
                  color: Colors.amber,
                  padding: const EdgeInsets.all(16),
                  child: const Row(
                    mainAxisAlignment: MainAxisAlignment.spaceAround,
                    children: [
                      Text('Take photo and apply filter',
                          style: TextStyle(fontSize: 30)),
                      Icon(
                        Icons.camera_alt_outlined,
                        size: 50,
                      )
                    ],
                  ),
                ),
              ),
            ),
            const SizedBox(height: 100),
            Row(
              mainAxisAlignment: MainAxisAlignment.spaceAround,
              children: [
                const Text(
                  'Filter selected:',
                  style: TextStyle(color: Colors.white, fontSize: 35),
                ),
                Container(
                  color: Colors.grey,
                  child: Padding(
                    padding: const EdgeInsets.all(8.0),
                    child: Row(
                      children: [
                        const Text('GreyScale Filter',
                            style:
                                TextStyle(color: Colors.white, fontSize: 25)),
                        const SizedBox(width: 25),
                        widget.selectedFilters[0] == 0
                            ? const Icon(
                                Icons.disabled_by_default_rounded,
                                color: Colors.red,
                                size: 45,
                              )
                            : Icon(
                                Icons.check_box,
                                color: Colors.green.shade900,
                                size: 45,
                              )
                      ],
                    ),
                  ),
                ),
                Container(
                  color: Colors.grey,
                  child: Padding(
                    padding: const EdgeInsets.all(8.0),
                    child: Row(
                      children: [
                        const Text('Sobel Filter',
                            style:
                                TextStyle(color: Colors.white, fontSize: 25)),
                        const SizedBox(width: 25),
                        widget.selectedFilters[1] == 0
                            ? const Icon(
                                Icons.disabled_by_default_rounded,
                                color: Colors.red,
                                size: 45,
                              )
                            : Icon(
                                Icons.check_box,
                                color: Colors.green.shade900,
                                size: 45,
                              )
                      ],
                    ),
                  ),
                ),
                Container(
                  color: Colors.grey,
                  child: Padding(
                    padding: const EdgeInsets.all(8.0),
                    child: Row(
                      children: [
                        const Text('Laplacian Filter',
                            style:
                                TextStyle(color: Colors.white, fontSize: 25)),
                        const SizedBox(width: 25),
                        widget.selectedFilters[2] == 0
                            ? const Icon(
                                Icons.disabled_by_default_rounded,
                                color: Colors.red,
                                size: 45,
                              )
                            : Icon(
                                Icons.check_box,
                                color: Colors.green.shade900,
                                size: 45,
                              )
                      ],
                    ),
                  ),
                ),
              ],
            ),
            const SizedBox(height: 25),
            Row(
              children: [
                const SizedBox(width: 20),
                const Text(
                  'Optimization:',
                  style: TextStyle(color: Colors.white, fontSize: 35),
                ),
                const SizedBox(width: 70),
                Container(
                  color: Colors.grey,
                  child: Padding(
                    padding: const EdgeInsets.all(8.0),
                    child: Row(
                      children: [
                        const Text('OpenMP',
                            style:
                                TextStyle(color: Colors.white, fontSize: 25)),
                        const SizedBox(width: 25),
                        widget.useOmp == 0
                            ? const Icon(
                                Icons.disabled_by_default_rounded,
                                color: Colors.red,
                                size: 45,
                              )
                            : Icon(
                                Icons.check_box,
                                color: Colors.green.shade900,
                                size: 45,
                              )
                      ],
                    ),
                  ),
                ),
              ],
            ),
          ],
        ),
      ),
    );
  }

  void _takePhoto() async {
    var response = await takePhoto();

    Image originalImage;
    Image filteredImage;

    if (response.statusCode == 200) {
      final bytes = response.bodyBytes;
      originalImage = Image.memory(
        bytes,
        width: 400,
        height: 250,
      );
      // Ahora puedes mostrar la imagen en tu aplicación Flutter
    } else {
      throw Exception('No se pudo cargar la imagen');
    }

    response = await applyPhotoFilter();

    response = await getFilteredImage();
    if (response.statusCode == 200) {
      final bytes = response.bodyBytes;
      filteredImage = Image.memory(
        bytes,
        width: 400,
        height: 250,
      );
      // Ahora puedes mostrar la imagen en tu aplicación Flutter
    } else {
      throw Exception('No se pudo cargar la imagen');
    }

    if (context.mounted) {
      _openBottomSheet(context, originalImage, filteredImage);
    }
  }

  void _openBottomSheet(
      BuildContext context, Image originalImage, Image filteredImage) {
    showModalBottomSheet(
      elevation: 0,
      isScrollControlled: true,
      context: context,
      builder: (BuildContext context) {
        return SizedBox(
          height: 700,
          child: StatefulBuilder(
            builder: (BuildContext context, StateSetter setState) {
              return Column(
                mainAxisAlignment: MainAxisAlignment.center,
                children: [
                  Row(
                    mainAxisAlignment: MainAxisAlignment.center,
                    children: [
                      Column(
                        children: [
                          const Text(
                            "Original photo:",
                            style: TextStyle(fontSize: 34),
                          ),
                          const SizedBox(height: 25),
                          originalImage,
                        ],
                      ),
                      const SizedBox(width: 100),
                      Column(
                        children: [
                          const Text(
                            "Filtered image:",
                            style: TextStyle(fontSize: 34),
                          ),
                          const SizedBox(height: 25),
                          filteredImage,
                        ],
                      ),
                    ],
                  ),
                  const SizedBox(height: 15),
                  Row(
                    mainAxisAlignment: MainAxisAlignment.center,
                    children: [
                      Column(
                        crossAxisAlignment: CrossAxisAlignment.start,
                        children: [
                          Text(
                              'Time elapsed no OMP: ${widget.timeElapsedNoOmp}ms',
                              style: const TextStyle(fontSize: 24)),
                          Text(
                              'Time elapsed with OMP: ${widget.timeElapsedOmp}ms',
                              style: const TextStyle(fontSize: 24)),
                          Text(
                              'Enhanced time with OMP: ${widget.timeElapsedNoOmp - widget.timeElapsedOmp}ms',
                              style: const TextStyle(fontSize: 24)),
                        ],
                      ),
                    ],
                  ),
                  const SizedBox(height: 15),
                  SizedBox(
                    width: 100,
                    height: 50,
                    child: ElevatedButton(
                        onPressed: () {
                          Navigator.pop(context);
                        },
                        child: const Text(
                          'Exit',
                          style: TextStyle(fontSize: 35),
                        )),
                  )
                ],
              );
            },
          ),
        );
      },
    );
  }
}
