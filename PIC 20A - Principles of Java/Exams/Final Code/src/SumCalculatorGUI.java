// Code for Problem 8

import javax.swing.*;
import java.awt.*;

public class SumCalculatorGUI {
    public static void SumCalculatorGUITest(String[] args) {
        GUI myGUI = new GUI();
    }
}

class GUI {

    // frame containing all our elements
    private JFrame guiFrame;
    private JTextField field1, field2, sumField;
    private JButton addButton;

    // constructor
    public GUI() {
        // initialising frame, text fields, and add button
        guiFrame = new JFrame();
        field1 = new JTextField();
        field2 = new JTextField();
        sumField = new JTextField();
        addButton = new JButton("Add");

        // formatting sum field
        sumField.setEditable(false);
        sumField.setBackground(Color.WHITE);

        // setting layout to GridLayout with 4 columns and 2 rows
        guiFrame.setLayout(new GridLayout(4, 2));
        // adding components in
        guiFrame.add(new JLabel("Number 1:"));
        guiFrame.add(field1);
        guiFrame.add(new JLabel("Number 2:"));
        guiFrame.add(field2);
        guiFrame.add(new JLabel("Sum:"));
        guiFrame.add(sumField);
        guiFrame.add(addButton);

        // adding action listener to the add button
        addButton.addActionListener(e -> {
            // extracting numbers in fields 1 and 2
            int number1 = Integer.parseInt(field1.getText());
            int number2 = Integer.parseInt(field2.getText());
            // adding and setting text for sumField
            sumField.setText(Integer.toString(number1 + number2));
        });

        // setting default close operation, size, et cetera on guiFrame
        guiFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        guiFrame.setSize(400, 200);
        guiFrame.setVisible(true);
    }
}
