#ifndef IMAGE_MANIPULATION_H
#define IMAGE_MANIPULATION_H

#include <iostream>
#include <QImage>
#include <QDataStream>
#include <QDebug>
#include <QImageIOPlugin>

#include <vector>


#include "OpenEXR/ImfInputFile.h"

#include "OpenEXR/ImfArray.h"
#include "OpenEXR/ImfRgba.h"
#include "OpenEXR/ImfCRgbaFile.h"




namespace ms{

    bool readExr(QImage *outImage);



}   // End of namespace ms

#endif // IMAGE_MANIPULATION_H
