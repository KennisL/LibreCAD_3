#include <map>
#include "cad/primitive/dimaligned.h"


using namespace lc;
using namespace entity;

DimAligned::DimAligned(geo::Coordinate const& definitionPoint, geo::Coordinate const& middleOfText, TextConst::AttachmentPoint const& attachmentPoint, double textAngle, double const lineSpacingFactor,
                       TextConst::LineSpacingStyle const& lineSpacingStyle, std::string const& explicitValue,
                       geo::Coordinate const& definitionPoint2, geo::Coordinate const& definitionPoint3, const Layer_CSPtr layer, const MetaInfo_CSPtr metaInfo):
    CADEntity(layer, metaInfo), Dimension(definitionPoint, middleOfText, attachmentPoint, textAngle, lineSpacingFactor, lineSpacingStyle, explicitValue),
    _definitionPoint2(definitionPoint2), _definitionPoint3(definitionPoint3) {

}


DimAligned::DimAligned(const DimAligned_CSPtr other, bool sameID) : CADEntity(other, sameID), Dimension(*other), _definitionPoint2(other->_definitionPoint2), _definitionPoint3(other->_definitionPoint3) {
}

DimAligned_SPtr DimAligned::dimAuto(geo::Coordinate const& p1, geo::Coordinate const& p2, geo::Coordinate const& middleOfText, std::string const& explicitValue, const Layer_CSPtr layer, const MetaInfo_CSPtr metaInfo) {
    auto nearestPoint = geo::Vector(p1, p2).nearestPointOnPath(middleOfText);
    auto distance = nearestPoint.distanceTo(middleOfText);

    geo::Coordinate dir;
    if(((p2.x() - p1.x()) * (middleOfText.y() - p1.y()) - (p2.y() - p1.y()) * (middleOfText.x() - p1.x())) >= 0) {
        dir = (p2 - p1).rotate(0.5 * M_PI);
    }
    else {
        dir = (p2 - p1).rotate(-0.5 * M_PI);
    }

    geo::Coordinate p0 = p2.move(dir, distance);

    return std::make_shared<DimAligned>(p0, middleOfText, TextConst::AttachmentPoint::Top_center , 0., 0., TextConst::LineSpacingStyle::AtLeast, explicitValue, p1, p2, layer, metaInfo);
}



CADEntity_CSPtr DimAligned::move(const geo::Coordinate& offset) const {
    auto newDimAligned = std::make_shared<DimAligned>(this->definitionPoint() + offset, this->middleOfText() + offset, this->attachmentPoint(), this->textAngle(), this->lineSpacingFactor(), this->lineSpacingStyle(), this->explicitValue(),  this->_definitionPoint2 + offset,  this->_definitionPoint3 + offset,  this->layer(), this->metaInfo());
    newDimAligned->setID(this->id());
    return newDimAligned;
}

CADEntity_CSPtr DimAligned::copy(const geo::Coordinate& offset) const {
    auto newDimAligned = std::make_shared<DimAligned>(this->definitionPoint() + offset, this->middleOfText() + offset, this->attachmentPoint(), this->textAngle(), this->lineSpacingFactor(), this->lineSpacingStyle(), this->explicitValue(),  this->_definitionPoint2 + offset, this->_definitionPoint3 + offset,  this->layer(), this->metaInfo());
    return newDimAligned;
}

CADEntity_CSPtr DimAligned::rotate(const geo::Coordinate& rotation_center, const double rotation_angle) const {
    auto newDimAligned = std::make_shared<DimAligned>(this->definitionPoint().rotate(rotation_center, rotation_angle),
                                                      this->middleOfText().rotate(rotation_center, rotation_angle), this->attachmentPoint(), this->textAngle(), this->lineSpacingFactor(), this->lineSpacingStyle(), this->explicitValue(), this->_definitionPoint2.rotate(rotation_center, rotation_angle), this->_definitionPoint3.rotate(rotation_center, rotation_angle),  this->layer(), this->metaInfo());
    return newDimAligned;
}

CADEntity_CSPtr DimAligned::scale(const geo::Coordinate& scale_center, const geo::Coordinate& scale_factor) const {
    auto newDimAligned = std::make_shared<DimAligned>(this->definitionPoint().scale(scale_center, scale_factor),
                                                      this->middleOfText().scale(scale_center, scale_factor), this->attachmentPoint(), this->textAngle(), this->lineSpacingFactor(), this->lineSpacingStyle(), this->explicitValue(), this->_definitionPoint2.scale(scale_center, scale_factor), this->_definitionPoint3.scale(scale_center, scale_factor),  this->layer(), this->metaInfo());
    return newDimAligned;
}

CADEntity_CSPtr DimAligned::mirror(const geo::Coordinate& axis1,
                    const geo::Coordinate& axis2) const {

    auto newDimAligned = std::make_shared<DimAligned>(this->definitionPoint().mirror(axis1, axis2),
                                                      this->middleOfText().mirror(axis1, axis2), this->attachmentPoint(), this->textAngle(), this->lineSpacingFactor(), this->lineSpacingStyle(), this->explicitValue(), this->_definitionPoint2.mirror(axis1, axis2), this->_definitionPoint3.mirror(axis1, axis2),  this->layer(), this->metaInfo());
    return newDimAligned;
}

const geo::Area DimAligned::boundingBox() const {
    // TODO create proper bounding box for DimAligned
    return geo::Area(this->middleOfText(), 0., 0.);
}

CADEntity_CSPtr DimAligned::modify(Layer_CSPtr layer, const MetaInfo_CSPtr metaInfo) const {
    auto newDimAligned = std::make_shared<DimAligned>(
                             this->definitionPoint(), this->middleOfText(), this->attachmentPoint(), this->textAngle(), this->lineSpacingFactor(), this->lineSpacingStyle(), this->explicitValue(), this->_definitionPoint2, this->_definitionPoint3,  this->layer(), metaInfo);
    return newDimAligned;
}

const geo::Coordinate& DimAligned::definitionPoint2() const noexcept {
    return _definitionPoint2;
}
const geo::Coordinate& DimAligned::definitionPoint3() const noexcept {
    return _definitionPoint3;
}

std::map<unsigned int, geo::Coordinate> DimAligned::dragPoints() const {
    std::map<unsigned int, geo::Coordinate> dragPoints;

    dragPoints[0] = definitionPoint();
    dragPoints[1] = middleOfText();
    dragPoints[2] = _definitionPoint2;
    dragPoints[3] = _definitionPoint3;

    return dragPoints;
}


CADEntity_CSPtr DimAligned::setDragPoints(std::map<unsigned int, lc::geo::Coordinate> dragPoints) const {
    try {
        auto newEntity = std::make_shared<DimAligned>(dragPoints.at(0),
                                                      dragPoints.at(1),
                                                      attachmentPoint(),
                                                      textAngle(),
                                                      lineSpacingFactor(),
                                                      lineSpacingStyle(),
                                                      explicitValue(),
                                                      dragPoints.at(2),
                                                      dragPoints.at(3),
                                                      layer(),
                                                      metaInfo());
        newEntity->setID(id());
        return newEntity;
    }
    catch(std::out_of_range& e) {
        return shared_from_this();
    }
}

