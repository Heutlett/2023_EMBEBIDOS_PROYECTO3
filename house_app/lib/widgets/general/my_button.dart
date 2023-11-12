import 'package:flutter/material.dart';

import 'my_text.dart';

class MyButton extends StatelessWidget {
  final String text;
  final VoidCallback function;
  final double fontSize;
  final Size size;
  final Color backgroundColor;
  final Color foregroundColor;
  final IconData? icon;

  const MyButton({
    super.key,
    required this.text,
    required this.function,
    this.fontSize = 18,
    this.size = const Size(200, 60),
    this.backgroundColor = Colors.blue,
    this.foregroundColor = Colors.white,
    this.icon,
  });

  @override
  Widget build(BuildContext context) {
    return ElevatedButton(
      onPressed: function,
      style: ElevatedButton.styleFrom(
        fixedSize: size,
        backgroundColor: backgroundColor,
      ),
      child: icon == null
          ? MyText(
              text: text,
              fontSize: fontSize,
              color: foregroundColor,
            )
          : Row(
              children: [
                Icon(icon),
                const SizedBox(width: 9),
                MyText(
                  text: text,
                  fontSize: fontSize,
                  color: foregroundColor,
                ),
              ],
            ),
    );
  }
}
