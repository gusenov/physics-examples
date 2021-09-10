#include "myquickview.h"

MyQuickView::MyQuickView()
{
    // Делает так, чтобы при изменении окна QQuickView автоматически
    // производились изменения размеров основного QМL-элемента в соответствии с новыми
    // размерами окна.
    setResizeMode(QQuickView::SizeRootObjectToView);
}
