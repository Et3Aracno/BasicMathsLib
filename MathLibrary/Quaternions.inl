#pragma once


template<typename T>
Maths::Quat<T> Maths::Quat<T>::Cross(const Quat<T>& b) const {
    // Produit vectoriel seulement sur x,y,z (ignore w)
    return Maths::Quat<T>(
        0,
        GetY() * b.GetZ() - GetZ() * b.GetY(),
        GetZ() * b.GetX() - GetX() * b.GetZ(),
        GetX() * b.GetY() - GetY() * b.GetX()
    );
}



template<typename T>
T Maths::Quat<T>::Magnitude() const {
    return std::sqrt(GetW() * GetW() + GetX() * GetX() + GetY() * GetY() + GetZ() * GetZ());
}


template<typename T>
void Maths::Quat<T>::Normalize()
{
    T mag = std::sqrt(GetW() * GetW() + GetX() * GetX() + GetY() * GetY() + GetZ() * GetZ());

    if (mag > std::numeric_limits<T>::epsilon()) {
        SetW(GetW() / mag);
        SetX(GetX() / mag);
        SetY(GetY() / mag);
        SetZ(GetZ() / mag);
    }
    else {
        SetW(T(1));
        SetX(T(0));
        SetY(T(0));
        SetZ(T(0));
    }
}


template<typename T>
Maths::Quat<T> Maths::Quat<T>::normalized() const
{
    T mag = std::sqrt(GetW() * GetW() + GetX() * GetX() + GetY() * GetY() + GetZ() * GetZ());

    if (mag > std::numeric_limits<T>::epsilon()) {
        Quat<T> result;
        result.SetW(GetW() / mag);
        result.SetX(GetX() / mag);
        result.SetY(GetY() / mag);
        result.SetZ(GetZ() / mag);
        return result;
    }
    else {
        Quat<T> identity;
        identity.SetW(1);
        identity.SetX(0);
        identity.SetY(0);
        identity.SetZ(0);
        return identity;
    }
}




template<typename T>
T Maths::Quat<T>::Dot(const Quat<T>& b)
{
    return GetW() * b.GetW() +
        GetX() * b.GetX() +
        GetY() * b.GetY() +
        GetZ() * b.GetZ();
}

template<typename T>
Maths::Quat<T> Maths::Quat<T>::Lerp(const Quat<T>& b, T t)
{
    
    if (t < 0) t = 0;
    if (t > 1) t = 1;

   
    T w = GetW() * (1 - t) + b.GetW() * t;
    T x = GetX() * (1 - t) + b.GetX() * t;
    T y = GetY() * (1 - t) + b.GetY() * t;
    T z = GetZ() * (1 - t) + b.GetZ() * t;

    
    Quat<T> result(w, x, y, z);

    
    result.Normalize();

    return result;
}


template<typename T>
Maths::Quat<T> Maths::Quat<T>::LerpUnclamped(const Quat<T>& b, T t)
{
    
    T w = GetW() * (1 - t) + b.GetW() * t;
    T x = GetX() * (1 - t) + b.GetX() * t;
    T y = GetY() * (1 - t) + b.GetY() * t;
    T z = GetZ() * (1 - t) + b.GetZ() * t;

    Quat<T> result(w, x, y, z);
    result.Normalize();

    return result;
}


template<typename T>
Maths::Quat<T> Maths::Quat<T>::Slerp(const Quat<T>& b, T t)
{
   
    T dot = GetW() * b.GetW() + GetX() * b.GetX() + GetY() * b.GetY() + GetZ() * b.GetZ();

   
    Quat<T> bCopy = b;
    if (dot < 0.0f) {
        dot = -dot;
        bCopy = Quat<T>(-b.GetW(), -b.GetX(), -b.GetY(), -b.GetZ());
    }


    if (dot > 0.9995f) {
        T w = GetW() + t * (bCopy.GetW() - GetW());
        T x = GetX() + t * (bCopy.GetX() - GetX());
        T y = GetY() + t * (bCopy.GetY() - GetY());
        T z = GetZ() + t * (bCopy.GetZ() - GetZ());
        Quat<T> result(w, x, y, z);
        result.Normalize();
        return result;
    }

   
    T theta_0 = std::acos(dot);
    T theta = theta_0 * t;

 
    Quat<T> c(bCopy.GetW() - GetW() * dot,
        bCopy.GetX() - GetX() * dot,
        bCopy.GetY() - GetY() * dot,
        bCopy.GetZ() - GetZ() * dot);
    c.Normalize();

    Quat<T> result(
        GetW() * std::cos(theta) + c.GetW() * std::sin(theta),
        GetX() * std::cos(theta) + c.GetX() * std::sin(theta),
        GetY() * std::cos(theta) + c.GetY() * std::sin(theta),
        GetZ() * std::cos(theta) + c.GetZ() * std::sin(theta)
    );

    return result;
}


template<typename T>
Maths::Quat<T> Maths::Quat<T>::SlerpUnclamped(const Quat<T>& b, T t)
{
    T dot = GetW() * b.GetW() + GetX() * b.GetX() + GetY() * b.GetY() + GetZ() * b.GetZ();

    Quat<T> bCopy = b;
    if (dot < 0.0f) {
        dot = -dot;
        bCopy = Quat<T>(-b.GetW(), -b.GetX(), -b.GetY(), -b.GetZ());
    }

    if (dot > 0.9995f) {
        T w = GetW() + t * (bCopy.GetW() - GetW());
        T x = GetX() + t * (bCopy.GetX() - GetX());
        T y = GetY() + t * (bCopy.GetY() - GetY());
        T z = GetZ() + t * (bCopy.GetZ() - GetZ());
        Quat<T> result(w, x, y, z);
        result.Normalize();
        return result;
    }

    T theta_0 = std::acos(dot);
    T theta = theta_0 * t;

    Quat<T> c(
        bCopy.GetW() - GetW() * dot,
        bCopy.GetX() - GetX() * dot,
        bCopy.GetY() - GetY() * dot,
        bCopy.GetZ() - GetZ() * dot
    );
    c.Normalize();

    Quat<T> result(
        GetW() * std::cos(theta) + c.GetW() * std::sin(theta),
        GetX() * std::cos(theta) + c.GetX() * std::sin(theta),
        GetY() * std::cos(theta) + c.GetY() * std::sin(theta),
        GetZ() * std::cos(theta) + c.GetZ() * std::sin(theta)
    );

    return result;
}


template<typename T>
void Maths::Quat<T>::LookRotation(const Quat<T>& forward, const Quat<T>& up)
{
  
    Quat<T> f = forward;
    f.Normalize();

    Quat<T> u = up;
    u.Normalize();

    // Calcul du vecteur droit (right)
    Quat<T> r(
        f.GetY() * u.GetZ() - f.GetZ() * u.GetY(),
        f.GetZ() * u.GetX() - f.GetX() * u.GetZ(),
        f.GetX() * u.GetY() - f.GetY() * u.GetX(),
        0
    );
    r.Normalize();

    // Recalcul du vecteur up
    u = Quat<T>(
        r.GetY() * f.GetZ() - r.GetZ() * f.GetY(),
        r.GetZ() * f.GetX() - r.GetX() * f.GetZ(),
        r.GetX() * f.GetY() - r.GetY() * f.GetX(),
        0
    );

    // Matrice 3x3
    T m00 = r.GetX(), m01 = r.GetY(), m02 = r.GetZ();
    T m10 = u.GetX(), m11 = u.GetY(), m12 = u.GetZ();
    T m20 = -f.GetX(), m21 = -f.GetY(), m22 = -f.GetZ();

    T trace = m00 + m11 + m22;
    if (trace > 0) {
        T s = std::sqrt(trace + 1.0) * 2;
        SetW(0.25 * s);
        SetX((m21 - m12) / s);
        SetY((m02 - m20) / s);
        SetZ((m10 - m01) / s);
    }
    else if ((m00 > m11) && (m00 > m22)) {
        T s = std::sqrt(1.0 + m00 - m11 - m22) * 2;
        SetW((m21 - m12) / s);
        SetX(0.25 * s);
        SetY((m01 + m10) / s);
        SetZ((m02 + m20) / s);
    }
    else if (m11 > m22) {
        T s = std::sqrt(1.0 + m11 - m00 - m22) * 2;
        SetW((m02 - m20) / s);
        SetX((m01 + m10) / s);
        SetY(0.25 * s);
        SetZ((m12 + m21) / s);
    }
    else {
        T s = std::sqrt(1.0 + m22 - m00 - m11) * 2;
        SetW((m10 - m01) / s);
        SetX((m02 + m20) / s);
        SetY((m12 + m21) / s);
        SetZ(0.25 * s);
    }

    Normalize();
}


template<typename T>
void Maths::Quat<T>::SetLookRotation(const Quat<T>& forward, const Quat<T>& up)
{

    Quat<T> f = forward;
    f.Normalize();

    Quat<T> u = up;
    u.Normalize();

    Quat<T> r(
        f.GetY() * u.GetZ() - f.GetZ() * u.GetY(),
        f.GetZ() * u.GetX() - f.GetX() * u.GetZ(),
        f.GetX() * u.GetY() - f.GetY() * u.GetX(),
        0
    );
    r.Normalize();

    u = Quat<T>(
        r.GetY() * f.GetZ() - r.GetZ() * f.GetY(),
        r.GetZ() * f.GetX() - r.GetX() * f.GetZ(),
        r.GetX() * f.GetY() - r.GetY() * f.GetX(),
        0
    );

    T m00 = r.GetX(), m01 = r.GetY(), m02 = r.GetZ();
    T m10 = u.GetX(), m11 = u.GetY(), m12 = u.GetZ();
    T m20 = -f.GetX(), m21 = -f.GetY(), m22 = -f.GetZ();

    T trace = m00 + m11 + m22;
    if (trace > 0) {
        T s = std::sqrt(trace + 1.0) * 2;
        SetW(0.25 * s);
        SetX((m21 - m12) / s);
        SetY((m02 - m20) / s);
        SetZ((m10 - m01) / s);
    }
    else if ((m00 > m11) && (m00 > m22)) {
        T s = std::sqrt(1.0 + m00 - m11 - m22) * 2;
        SetW((m21 - m12) / s);
        SetX(0.25 * s);
        SetY((m01 + m10) / s);
        SetZ((m02 + m20) / s);
    }
    else if (m11 > m22) {
        T s = std::sqrt(1.0 + m11 - m00 - m22) * 2;
        SetW((m02 - m20) / s);
        SetX((m01 + m10) / s);
        SetY(0.25 * s);
        SetZ((m12 + m21) / s);
    }
    else {
        T s = std::sqrt(1.0 + m22 - m00 - m11) * 2;
        SetW((m10 - m01) / s);
        SetX((m02 + m20) / s);
        SetY((m12 + m21) / s);
        SetZ(0.25 * s);
    }

    Normalize();
}



template<typename T>
void Maths::Quat<T>::RotateTowards(const Quat<T>& to, T maxDegreesDelta)
{
  
    T dot = GetW() * to.GetW() + GetX() * to.GetX() + GetY() * to.GetY() + GetZ() * to.GetZ();

    T angle = std::acos(std::min(std::abs(dot), static_cast<T>(1.0))) * 2.0 * (180.0 / 3.14159265);

    if (angle <= maxDegreesDelta)
    {
        SetW(to.GetW());
        SetX(to.GetX());
        SetY(to.GetY());
        SetZ(to.GetZ());
        return;
    }

    T t = maxDegreesDelta / angle;

    Quat<T> result;
    T theta = std::acos(dot);
    T sinTheta = std::sin(theta);

    if (sinTheta > 1e-6) {
        T ratioA = std::sin((1 - t) * theta) / sinTheta;
        T ratioB = std::sin(t * theta) / sinTheta;

        result.SetW(GetW() * ratioA + to.GetW() * ratioB);
        result.SetX(GetX() * ratioA + to.GetX() * ratioB);
        result.SetY(GetY() * ratioA + to.GetY() * ratioB);
        result.SetZ(GetZ() * ratioA + to.GetZ() * ratioB);
    }
    else {
        result.SetW(GetW() * (1 - t) + to.GetW() * t);
        result.SetX(GetX() * (1 - t) + to.GetX() * t);
        result.SetY(GetY() * (1 - t) + to.GetY() * t);
        result.SetZ(GetZ() * (1 - t) + to.GetZ() * t);
    }

    SetW(result.GetW());
    SetX(result.GetX());
    SetY(result.GetY());
    SetZ(result.GetZ());

    Normalize();
}



template<typename T>
void Maths::Quat<T>::setFromToRotation(const Quat<T>& to)
{
   
    Quat<T> fromVec(0, GetX(), GetY(), GetZ());
    Quat<T> toVec(0, to.GetX(), to.GetY(), to.GetZ());

    T dot = fromVec.GetX() * toVec.GetX() + fromVec.GetY() * toVec.GetY() + fromVec.GetZ() * toVec.GetZ();
    dot = std::clamp(dot, static_cast<T>(-1.0), static_cast<T>(1.0));

    if (dot > static_cast<T>(0.9999)) {
        SetW(1);
        SetX(0); SetY(0); SetZ(0);
        return;
    }

    if (dot < static_cast<T>(-0.9999)) {
        Quat<T> orthoAxis;
        if (std::abs(fromVec.GetX()) < std::abs(fromVec.GetZ())) {
            orthoAxis = Quat<T>(0, 0, -fromVec.GetZ(), fromVec.GetY());
        }
        else {
            orthoAxis = Quat<T>(0, -fromVec.GetY(), fromVec.GetX(), 0);
        }
        orthoAxis.Normalize();
        AngleAxis(static_cast<T>(3.14159265), orthoAxis);
        return;
    }

 
    Quat<T> rotationAxis(0,
        fromVec.GetY() * toVec.GetZ() - fromVec.GetZ() * toVec.GetY(),
        fromVec.GetZ() * toVec.GetX() - fromVec.GetX() * toVec.GetZ(),
        fromVec.GetX() * toVec.GetY() - fromVec.GetY() * toVec.GetX());

    rotationAxis.Normalize();

    T angle = std::acos(dot);
    AngleAxis(angle, rotationAxis);
}


template<typename T>
void Maths::Quat<T>::ToAngleAxis(T& angle, Quat<T>& axis) const
{
    Quat<T> qNorm = *this;
    qNorm.Normalize();

    angle = 2 * std::acos(std::clamp(qNorm.GetW(), static_cast<T>(-1), static_cast<T>(1)));
    T s = std::sqrt(1 - qNorm.GetW() * qNorm.GetW()); 

    if (s < 1e-6) { 
        axis = Quat<T>(0, 1, 0, 0); 
    }
    else {
        axis = Quat<T>(0, qNorm.GetX() / s, qNorm.GetY() / s, qNorm.GetZ() / s); 
    }
}


template<typename T>
void Maths::Quat<T>::AngleAxis(T angle, const Quat<T>& axis)
{
    T halfAngle = angle / 2;
    T s = std::sin(halfAngle);

    SetW(std::cos(halfAngle));
    SetX(axis.GetX() * s);
    SetY(axis.GetY() * s);
    SetZ(axis.GetZ() * s);

    Normalize();
}


template<typename T>
void Maths::Quat<T>::Angle(T angle, T ax, T ay, T az)
{
    
    T mag = std::sqrt(ax * ax + ay * ay + az * az);
    if (mag == 0) {
  
        SetW(1);
        SetX(0);
        SetY(0);
        SetZ(0);
        return;
    }


    T nx = ax / mag;
    T ny = ay / mag;
    T nz = az / mag;


    T halfAngle = angle / 2;
    T s = std::sin(halfAngle);

    SetW(std::cos(halfAngle));
    SetX(nx * s);
    SetY(ny * s);
    SetZ(nz * s);


    Normalize();
}


template<typename T>
void Maths::Quat<T>::FromToRotation(const Quat<T>& to)
{
    
    Quat<T> f = this->normalized();
    Quat<T> t = to.normalized();

    T cosTheta = f.Dot(t);
    Quat<T> rotationAxis;

    if (cosTheta >= 1.0 - static_cast<T>(1e-6)) {
        SetW(1);
        SetX(0);
        SetY(0);
        SetZ(0);
        return;
    }

    if (cosTheta <= -1.0 + static_cast<T>(1e-6)) {
        rotationAxis = Quat<T>(0, 1, 0, 0).Cross(f);
        if (rotationAxis.Magnitude() < static_cast<T>(1e-6))
            rotationAxis = Quat<T>(1, 0, 0, 0).Cross(f);
        rotationAxis.Normalize();
        Angle(static_cast<T>(3.14159265), rotationAxis.GetX(), rotationAxis.GetY(), rotationAxis.GetZ());
        return;
    }

    rotationAxis = f.Cross(t);
    T angle = std::acos(std::clamp(cosTheta, static_cast<T>(-1), static_cast<T>(1)));
    rotationAxis.Normalize();
    Angle(angle, rotationAxis.GetX(), rotationAxis.GetY(), rotationAxis.GetZ());
}

template<typename T>
void Maths::Quat<T>::Inverse()
{
    T normSq = GetW() * GetW() + GetX() * GetX() + GetY() * GetY() + GetZ() * GetZ();
    if (normSq == 0) {
        throw std::runtime_error("Impossible d'inverser un quaternion nul");
    }

    SetW(GetW() / normSq);
    SetX(-GetX() / normSq);
    SetY(-GetY() / normSq);
    SetZ(-GetZ() / normSq);
}


template<typename T>
bool Maths::Quat<T>::Equals(const Quat<T>& q) const
{
    const T epsilon = 1e-6;

    return (std::abs(GetW() - q.GetW()) < epsilon) &&
        (std::abs(GetX() - q.GetX()) < epsilon) &&
        (std::abs(GetY() - q.GetY()) < epsilon) &&
        (std::abs(GetZ() - q.GetZ()) < epsilon);
}

template<typename T>
void Maths::Quat<T>::EuleurAngles(T& pitch, T& yaw, T& roll) const
{
  
    T sinp = 2 * (GetW() * GetY() - GetZ() * GetX());

   
    pitch = std::atan2(2 * (GetW() * GetX() + GetY() * GetZ()), 1 - 2 * (GetX() * GetX() + GetY() * GetY()));

    
    if (sinp >= 1)
        yaw = 3.14159265f / 2;  // 90 degr�s
    else if (sinp <= -1)
        yaw = -3.14159265f / 2; // -90 degr�s
    else
        yaw = std::asin(sinp);

   
    roll = std::atan2(2 * (GetW() * GetZ() + GetX() * GetY()), 1 - 2 * (GetY() * GetY() + GetZ() * GetZ()));
}






