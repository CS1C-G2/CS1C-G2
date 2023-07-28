#ifndef TEXTEDIT_H
#define TEXTEDIT_H
class TextEdit : public QTextEdit
{
protected:
    void keyPressEvent(QKeyEvent* event) override
    {
        if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
        {
            // Ignore the Enter or Return key press event
            event->ignore();
        }
        else
        {
            // Process all other key press events normally
            QTextEdit::keyPressEvent(event);
        }
    }
};
#endif // TEXTEDIT_H
