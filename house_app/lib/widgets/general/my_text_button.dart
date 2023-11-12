import 'package:flutter/material.dart';

import 'my_text.dart';

class MyTextButton extends StatelessWidget {
  final String text;
  final VoidCallback function;
  final double fontSize;
  final Size size;
  final Color backgroundColor;
  final Color foregroundColor;
  final IconData? icon;

  const MyTextButton({
    super.key,
    required this.text,
    required this.function,
    this.fontSize = 14,
    this.size = const Size(120, 20),
    this.backgroundColor = Colors.white,
    this.foregroundColor = Colors.blue,
    this.icon,
  });

  @override
  Widget build(BuildContext context) {
    return TextButton(
      onPressed: function,
      style: TextButton.styleFrom(
        fixedSize: size,
        backgroundColor: backgroundColor,
      ),
      child: Row(
        children: [
          Icon(
            icon,
            color: foregroundColor,
          ),
          const SizedBox(width: 8),
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
