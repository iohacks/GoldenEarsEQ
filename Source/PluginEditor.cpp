/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GoldenEarsEqAudioProcessorEditor::GoldenEarsEqAudioProcessorEditor(GoldenEarsEqAudioProcessor &p)
        : AudioProcessorEditor(&p), processor(p) {
    // Add the freqList header
    lblFreqListHeader.setText("Select the Band Pass Frequency", NotificationType::sendNotification);
    lblFreqListHeader.setJustificationType(Justification::centred);
    lblFreqListHeader.setBounds(10, 10, 620, 50);
    addAndMakeVisible(lblFreqListHeader);

    // Initialize answer list
    int x = 10;
    int y = 70;
    int width = 80;
    int height = 40;

    Array<float> freqList = processor.bandPassGame.getFreqList();
    for (float freq: freqList) {
        TextButton *button = new TextButton(String((int) freq));
        button->setBounds(x, y, width, height);
        x += width + 10;
        button->onClick = [this, freq]() {
            processor.bandPassGame.setAnswer(freq);
            repaint();
        };
        btnFreqList.add(button);
        addAndMakeVisible(button);
    }

    // Initialize the start button
    btnStart.setButtonText("Start");
    btnStart.setBounds(10, 10, 620, 100);
    btnStart.onClick = [this]() {
        processor.bandPassGame.start();
        repaint();
    };
    addAndMakeVisible(btnStart);

    // Initialize result
    lblResult.setBounds(10, 110, 620, 50);
    lblResult.setJustificationType(Justification::centred);
    addAndMakeVisible(lblResult);

    setSize(640, 300);
}

GoldenEarsEqAudioProcessorEditor::~GoldenEarsEqAudioProcessorEditor() {
    for (TextButton *button: btnFreqList) {
        delete button;
    }
}

//==============================================================================
void GoldenEarsEqAudioProcessorEditor::paint(Graphics &g) {
    bool gameStarted = processor.bandPassGame.isStarted();

    // handle answer list rendering
    lblFreqListHeader.setVisible(gameStarted ? true : false);
    for (TextButton *button: btnFreqList) {
        button->setVisible(gameStarted ? true : false);
    }

    // handle start button rendering
    btnStart.setVisible(gameStarted ? false : true);

    // handle result rendering
    if (gameStarted) {
        lblResult.setVisible(false);
    } else {
        float correctAnswer = processor.bandPassGame.getCurrentFreq();
        float givenAnswer = processor.bandPassGame.getAnswer();
        bool isCorrect = correctAnswer == givenAnswer;
        String message = isCorrect ? "You are correct." : "It's " + String(correctAnswer) + ". (Your answer: " + String(givenAnswer) + ")";

        lblResult.setColour(Label::textColourId, isCorrect ? Colour(0, 255, 0) : Colour(255, 0, 0));
        if (correctAnswer == 0.0f) {
            lblResult.setVisible(false);
        } else {
            lblResult.setText(message, NotificationType::sendNotification);
            lblResult.setVisible(true);
        }
    }
}

void GoldenEarsEqAudioProcessorEditor::resized() {
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
