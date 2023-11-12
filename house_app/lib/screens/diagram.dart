import 'package:flutter/material.dart';
import 'package:house_app/services/house_service.dart';

class DiagramScreen extends StatefulWidget {
  const DiagramScreen({super.key});

  @override
  State<DiagramScreen> createState() => _DiagramScreenState();
}

class _DiagramScreenState extends State<DiagramScreen> {
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
            const SizedBox(height: 250),
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
      originalImage = Image.memory(bytes);
      // Ahora puedes mostrar la imagen en tu aplicación Flutter
    } else {
      throw Exception('No se pudo cargar la imagen');
    }

    response = await applyPhotoFilter();

    response = await getFilteredImage();
    if (response.statusCode == 200) {
      final bytes = response.bodyBytes;
      filteredImage = Image.memory(bytes);
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
                crossAxisAlignment: CrossAxisAlignment.center,
                mainAxisAlignment: MainAxisAlignment.center,
                children: [
                  Row(
                    mainAxisAlignment: MainAxisAlignment.center,
                    children: [
                      Column(
                        children: [
                          const Text(
                            "Original photo:",
                            style: TextStyle(fontSize: 24),
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
                            style: TextStyle(fontSize: 24),
                          ),
                          const SizedBox(height: 25),
                          filteredImage,
                        ],
                      ),
                    ],
                  ),
                  const SizedBox(height: 55),
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

class Puerta extends StatefulWidget {
  final String name;
  final int angle;
  const Puerta({
    super.key,
    required this.name,
    required this.angle,
  });

  @override
  State<Puerta> createState() => _PuertaState();
}

class _PuertaState extends State<Puerta> {
  int isOpen = 0;

  @override
  void initState() {
    super.initState();

    // // Utiliza un Timer.periodic para obtener el estado del LED cada 2 segundos.
    // Timer.periodic(const Duration(seconds: 2), (timer) {
    //   getDoorState(widget.name).then((response) {
    //     setState(() {
    //       isOpen = jsonDecode(response.body)['data']['state'];
    //     });
    //   }).catchError((error) {});
    // });
  }

  @override
  Widget build(BuildContext context) {
    return Column(
      mainAxisAlignment: MainAxisAlignment.center,
      children: <Widget>[
        Transform.rotate(
          angle: widget.angle *
              3.14159265359 /
              180, // Ángulo de rotación en radianes (45 grados)
          child: Icon(
            isOpen == 0 ? Icons.door_back_door_outlined : Icons.door_back_door,
            size: 55,
            color: isOpen == 1 ? Colors.green : Colors.red,
          ),
        )
      ],
    );
  }
}
