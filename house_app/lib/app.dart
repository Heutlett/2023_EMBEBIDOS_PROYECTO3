import 'package:flutter/material.dart';
import 'package:house_app/screens/diagram.dart';

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Material App',
      initialRoute: "/diagram",
      routes: {
        "/diagram": (BuildContext context) => const DiagramScreen(),
      },
    );
  }
}
