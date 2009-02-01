#include "folderbutton.h"

FolderButton::FolderButton(int i) {
    this->index = i;
}

void FolderButton::btnClick() {
    emit this->clicked(this->index);
}
