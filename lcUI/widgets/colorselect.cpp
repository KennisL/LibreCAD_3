#include "colorselect.h"

ColorSelect::ColorSelect(QWidget *parent, bool showByLayer, bool showByBlock) :
    QComboBox(parent) {

    qIconSize = QSize(32, 32);
    setIconSize(qIconSize);

    setMaximumHeight(32);

    if(showByLayer) {
        addItem(BY_LAYER);
    }
    if(showByBlock) {
        addItem(BY_BLOCK);
    }

    addItem(CUSTOM);
    insertSeparator(count());

    for(auto color : QColor::colorNames()){
        QPixmap pixmap(qIconSize);
        pixmap.fill(color);
        addItem(QIcon(pixmap), color);
    }

    connect(this, SIGNAL(activated(const QString&)), this, SLOT(onActivated(const QString&)));
}

QColor ColorSelect::getColor() {
    if(currentText() == CUSTOM) {
        return _customColor;
    }
    else {
        return QColor(currentText());
    }
}

lc::MetaColor_CSPtr ColorSelect::metaColor() {
    QColor color = getColor();

    if(!color.isValid()) {
        return nullptr;
    }

    return std::make_shared<lc::MetaColor>(color.redF(), color.greenF(), color.blueF(), color.alphaF());
}

lc::Color ColorSelect::color() {
    QColor color = getColor();

    if(!color.isValid()) {
        return lc::Color();
    }

    return lc::Color(color.redF(), color.greenF(), color.blueF(), color.alphaF());
}

void ColorSelect::onActivated(const QString& text) {
    if(text == CUSTOM) {
        auto colorDialog = new QColorDialog(this);

        if(_customColor.isValid()) {
            colorDialog->setCurrentColor(_customColor);
        }
        colorDialog->show();

        connect(colorDialog, &QColorDialog::colorSelected, this, &ColorSelect::on_customColorChanged);
    }
}

void ColorSelect::on_customColorChanged(const QColor &color) {
    _customColor = color;
}