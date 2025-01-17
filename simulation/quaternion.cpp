﻿#include "quaternion.h"
#include <iostream>
#include <math.h>

Quaternion::Quaternion(float s, QVector3D v)
{
    this->s = s;
    this->v = v;
}

Quaternion &Quaternion::operator=(const Quaternion &other)
{
    this->s = other.s;
    this->v = other.v;
    return *this;
}

Quaternion &Quaternion::operator*=(float factor)
{
    this->s *= factor;
    this->v *= factor;
    return *this;
}

Quaternion &Quaternion::operator+=(const Quaternion &other)
{
    this->s += other.s;
    this->v += other.v;
    return *this;
}

QMatrix4x4 Quaternion::toMatrix()
{
    this->normalize();
    float a = s, b = v.x(), c = v.y(), d = v.z();
    float r[] = {1 - 2*c*c - 2*d*d, 2*b*c - 2*a*d, 2*b*d + 2*a*c, 0,
                    2*b*c + 2*a*d, 1 - 2*b*b - 2*d*d, 2*c*d - 2*a*b, 0,
                    2*b*d - 2*a*c, 2*c*d + 2*a*b, 1 - 2*b*b - 2*c*c, 0,
                    0, 0, 0, 1};
    return QMatrix4x4(r);
}

void Quaternion::normalize()
{
    float a = s, b = v.x(), c = v.y(), d = v.z();
    float norm = std::sqrt(a*a + b*b + c*c + d*d);
    this->s /= norm;
    this->v /= norm;
}

const Quaternion operator+(const Quaternion &q1, const Quaternion &q2)
{
    return Quaternion(q1.s + q2.s, q1.v + q2.v);
}

const Quaternion operator*(const Quaternion &q1, const Quaternion &q2)
{
    float s = q1.s*q2.s - QVector3D::dotProduct(q1.v, q2.v);
    QVector3D v = q1.s*q2.v + q2.s*q1.v + QVector3D::crossProduct(q1.v, q2.v);
    return Quaternion(s, v);
}

const Quaternion operator*(float factor, const Quaternion &quaternion)
{
    return Quaternion(quaternion.s * factor, quaternion.v * factor);
}

const Quaternion operator*(const Quaternion &quaternion, float factor)
{
    return factor * quaternion;
}

const Quaternion operator/(const Quaternion &quaternion, float divisor)
{
    return Quaternion(quaternion.s/divisor, quaternion.v/divisor);
}
