#ifndef FOLDERBUTTON_H
#define FOLDERBUTTON_H

#include <QPushButton>

class FolderButton : public QPushButton {
    Q_OBJECT

    public:
        FolderButton(int i);

    protected:
    private:
        int index;

    public slots:
        void btnClick();

        signals:
        void clicked(int);
};

#endif // FOLDERBUTTON_H
