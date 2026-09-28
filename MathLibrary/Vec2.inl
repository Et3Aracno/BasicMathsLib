#pragma once 
#include "Vec2.h"

//change la position en bas
template<typename T>
void  Maths::Vct2D<T>::down()
{
	SetX(0);
	SetY(-1);
}


//change la position en haut
template<typename T>
void Maths::Vct2D<T>::up()
{
	SetX(0);
	SetY(1);
}


//change la position � gauche
template<typename T>
void Maths::Vct2D<T>::left()
{
	SetX(-1);
	SetY(0);
}


//change la position � droite
template<typename T>
void Maths::Vct2D<T>::right()
{
	SetX(1);
	SetY(0);
}


//change la pos � 0 0
template<typename T>
void Maths::Vct2D<T>::zero()
{
	SetX(0);
	SetY(0);
}

//magnitude = racine carr�e de (x^2 + y^2)
template<typename T>
T Maths::Vct2D<T>::magnitude() const
{
	T m = GetX() * GetX() + GetY() * GetY();
	T r = std::sqrt(m);
	return r;
}


//sqrtMagnitude = racine carr�e de la magnitude
template<typename T>
T Maths::Vct2D<T>::sqrMagnitude() const
{
	T m = GetX() * GetX() + GetY() * GetY();
	return m;
}


//normalized = vecteur divis� par sa magnitude
template<typename T>
void Maths::Vct2D<T>::normalized()
{
	T m = GetX() * GetX() + GetY() * GetY();
	T r = std::sqrt(m);
	if (r == 0)
	{
		throw std::runtime_error("Magnitude nulle");
	}
	SetX(GetX() / r);
	SetY(GetY() / r);

}

template<typename T>
Maths::Vct2D<T> Maths::Vct2D<T>::Normalized() const
{
	T m = GetX() * GetX() + GetY() * GetY();
	T r = std::sqrt(m);
	if (r == 0)
	{
		throw std::runtime_error("Magnitude nulle");
	}
	return Vct2D<T>(GetX() / r, GetY() / r);

}


//Permet de changer la valeur � partir d'un index
template<typename T>
void Maths::Vct2D<T>::thisInt(T i, int index)
{
	if (index == 0)
	{
		SetX(i);
	}
	else if (index == 1)
	{
		SetY(i);
	}
	else
	{
		throw std::out_of_range("Index invalide");
	}
}




//change la position en  1 1
template<typename T>
void Maths::Vct2D<T>::one()
{
	SetX(1);
	SetY(1);
}


//change la pos � moins l'infini
template<typename T>
void Maths::Vct2D<T>::nega_tiveInfinity()
{
	if constexpr (std::is_floating_point_v<T>) {		//verifie si T est un type � virgule flottante
		SetX(-std::numeric_limits<T>::infinity());
		SetY(-std::numeric_limits<T>::infinity());
	}
	else {												//si T est un type entier
		SetX(std::numeric_limits<T>::lowest());
		SetY(std::numeric_limits<T>::lowest());
	}

}


//change la pos � plus l'infini
template<typename T>
void Maths::Vct2D<T>::positiveInfinity()
{
	if constexpr (std::is_floating_point_v<T>) {		//verifie si T est un type � virgule flottante
		SetX(std::numeric_limits<T>::infinity());
		SetY(std::numeric_limits<T>::infinity());
	}
	else {												//si T est un type entier
		SetX(std::numeric_limits<T>::max());
		SetY(std::numeric_limits<T>::max());
	}
}


// Equals, compare deux vecteurs et verifie s'ils sont �gaux
template<typename T>
bool Maths::Vct2D<T>::operator==(const Vct2D<T>& other) const
{
	return x == other.x && y == other.y;
}


// Transforme en string le vecteur
template<typename T>
void Maths::Vct2D<T>::ToString() const
{
	std::cout << "X: " << GetX() << " Y: " << GetY() << std::endl;
}


// Calcule l'angle entre deux vecteurs en degr�s
template<typename T>
T Maths::Vct2D<T>::Angle(const Vct2D<T>& other) const
{
	T ps = x * other.x + y * other.y;
	T m1 = std::sqrt(x * x + y * y);
	T m2 = std::sqrt(other.x * other.x + other.y * other.y);
	if (m1 != 0 && m2 != 0)
	{

		T cosAngle = std::clamp(ps / (m1 * m2), -1.0f, 1.0f);
		return std::acos(cosAngle) * (180.0f / 3.14159265f);
	}
	else
	{
		throw std::runtime_error("Magnitude nulle");
		return 0;
	}
}


//limite la taille du vecteur � une valeur maximale
template<typename T>
Maths::Vct2D<T> Maths::Vct2D<T>::ClampMagnitude(const Vct2D<T>& v, T maxLength)
{
	T m = v.GetX() * v.GetX() + v.GetY() * v.GetY();
	T r = std::sqrt(m);
	if (r > maxLength)
	{
		T re_scale = maxLength / r;
		return Vct2D<T>(v.GetX() * re_scale, v.GetY() * re_scale);
	}
	return v;
}

// Calcule la distance entre deux vecteurs
template<typename T>
T Maths::Vct2D<T>::Distance(const Vct2D<T>& other) const
{
	T dx = other.GetX() - GetX();
	T dy = other.GetY() - GetY();
	return std::sqrt(dx * dx + dy * dy);
}

// Calcule le produit scalaire entre deux vecteurs et renvoie un T
template<typename T>
T Maths::Vct2D<T>::Dot(const Vct2D<T>& other) const
{
	return GetX() * other.GetX() + GetY() * other.GetY();
}

template<typename T>
Maths::Vct2D<T> Maths::Vct2D<T>::LerpClamp(const Vct2D<T>& target, T t) const
{
	t = std::clamp(t, 0.0f, 1.0f); // Affectation de la valeur clamp�e � t sinon la valeur est ignorer
	T newX = GetX() + (target.GetX() - GetX()) * t;
	T newY = GetY() + (target.GetY() - GetY()) * t;

	return Vct2D<T>(newX, newY);
}


template<typename T>
Maths::Vct2D<T> Maths::Vct2D<T>::LerpUnClamp(const Vct2D<T>& target, T t) const
{
	T newX = GetX() + (target.GetX() - GetX()) * t;
	T newY = GetY() + (target.GetY() - GetY()) * t;

	return Vct2D<T>(newX, newY);
}


template<typename T>
Maths::Vct2D<T> Maths::Vct2D<T>::Max(const Vct2D<T>& other) const
{

	//if (GetX() > other.GetX() && GetY() > other.GetY())
	//{
	//	return Vct2D<T>(GetX(), GetY());
	//}
	//else if (GetX() > other.GetX() && GetY() < other.GetY())
	//{
	//	return Vct2D<T>(GetX(), other.GetY());									//ancienne version trop brut et longue
	//}
	//else if (GetX() < other.GetX() && GetY() > other.GetY())
	//{
	//	return Vct2D<T>(other.GetX(), GetY());
	//}
	//else if (GetX() < other.GetX() && GetY() < other.GetY())
	//{
	//	return Vct2D<T>(other.GetX(), other.GetY());
	//}
	T maxX = std::max(GetX(), other.GetX());
	T maxY = std::max(GetY(), other.GetY());
	return Vct2D<T>(maxX, maxY);
}


template<typename T>
Maths::Vct2D<T> Maths::Vct2D<T>::Min(const Vct2D<T>& other) const
{
	/*if (GetX() < other.GetX() && GetY() < other.GetY())
	{
		return Vct2D<T>(GetX(), GetY());
	}
	else if (GetX() < other.GetX() && GetY() > other.GetY())
	{
		return Vct2D<T>(GetX(), other.GetY());									//ancienne version trop brut et longue
	}
	else if (GetX() > other.GetX() && GetY() < other.GetY())
	{
		return Vct2D<T>(other.GetX(), GetY());
	}
	else if (GetX() > other.GetX() && GetY() > other.GetY())
	{
		return Vct2D<T>(other.GetX(), other.GetY());
	}*/

	T minX = std::min(GetX(), other.GetX());
	T minY = std::min(GetY(), other.GetY());
	return Vct2D<T>(minX, minY);
}

template<typename T>
Maths::Vct2D<T> Maths::Vct2D<T>::MoveTowards(Vct2D<T> target, T maxDistanceDelta) const
{
	T dX = target.GetX() - GetX();
	T dY = target.GetY() - GetY();
	T distance = std::sqrt(dX * dX + dY * dY);
	if (distance == 0 || (maxDistanceDelta >= 0 && distance <= maxDistanceDelta))
	{
		return target;
	}

	T r = maxDistanceDelta / distance;
	return Vct2D<T>(GetX() + dX * r, GetY() + dY * r);
}


template<typename T>
Maths::Vct2D<T> Maths::Vct2D<T>::Perpendicular(bool Sense) const
{
	if (Sense) {
		return Vct2D<T>(-GetY(), GetX());
	}
	else
	{
		return Vct2D<T>(GetY(), -GetX());
	}
}

template<typename T>
Maths::Vct2D<T> Maths::Vct2D<T>::Reflect(const Vct2D<T>& vct_normaliser) const
{
	if (vct_normaliser.magnitude() == 0)
	{
		throw std::runtime_error("Vecteur nulle");
	}

	Vct2D<T> Vn = vct_normaliser.Normalized();		//Vn = vecteur normalis�
	T dotPdt = this->Dot(Vn);				//dotPdt = dot product


	T rx = GetX() - 2 * dotPdt * Vn.GetX();
	T ry = GetY() - 2 * dotPdt * Vn.GetY();
	return Vct2D<T>(rx, ry);
}


template<typename T>
Maths::Vct2D<T> Maths::Vct2D<T>::Scale(const Vct2D<T>& other) const
{
	return Vct2D<T>(GetX() * other.GetX(), GetY() * other.GetY());
}


template<typename T>
T Maths::Vct2D<T>::SignedAngle(Vct2D<T>& other) const
{

	T angle = Vct2D<T>::Angle(other);
	T cross = GetX() * other.GetY() - GetY() * other.GetX();			//cross = cross product(product vectoriel)
	if (cross < 0)
	{
		angle = -angle;
	}
	return angle;


}

//template<typename T>
//MathsVct3D::Vct3D<T> MathsVct2D::Vct2D<T>::Transfo3D(Vct2D<T>& vct_transfo) const
//{
//	T x = vct_transfo.GetX();
//	T y = vct_transfo.GetY();
//	T z = 0;
//	
//	return MathsVct3D::Vct3D<T>(x, y, z);
//
//
//}

//template<typename T>
//MathsVct2D::Vct2D<T> MathsVct2D::Vct2D<T>::Transfo3d() const
//{
//}
