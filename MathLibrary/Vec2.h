#pragma once
#include <iostream>
#include <algorithm>
#include <type_traits>


namespace Maths {//Vct correspond à vecteur 


	template <typename T>
	class Vct2D {
	private:
		T x;
		T y;

		static_assert(std::is_arithmetic_v<T>);
	public:

		//Contructeur/ Destructeur de classe
		Vct2D(T x, T y) : x(x), y(y) {}
		Vct2D() : x(0), y(0) {}
		~Vct2D() {}

		template<typename TypeToCastTo>
		operator TypeToCastTo()
		{
			return TypeToCastTo{ x, y };
		}

	

		//Getter X

		T GetX() const { return x; }

		//Getter Y
		T GetY() const { return y; }

		
		
		//Méthode Vector2D
		void SetVector2D(T x, T y) {SetX(x);SetY(y);}

		//Setter X
		void SetX(T X) { x = X; }


		//Setter Y
		void SetY(T Y) { y = Y; }



		//Méthode

		//change la position en bas
		void down();
		
		//change la position en haut
		void up();

		//change la position à gauche
		void left();

		//change la position à droite
		void right();

		//change la position en  1 1
		void one();

		//change la pos à moins l'infini
		void nega_tiveInfinity();

		//change la pos à plus l'infini
		void positiveInfinity();

		//change la pos à 0 0
		void zero();

		//magnitude vecteur
		T magnitude() const;

		//sqrt de la magnitude
		T sqrMagnitude() const;

		//normalized = vecteur divisé par sa magnitude en modifiant le vecteur d'origine
		void normalized();

		//Normalized = vecteur divisé par sa magnitude sans modifier le vecteur d'origine
		Vct2D<T> Normalized() const;


		//Permet de changer la valeur  index
		void thisInt(T i , int index);


		//Equals, compare deux vecteurs et verifie s'ils sont égaux
		bool operator==(const Vct2D<T>& other) const;

		//transforme en string le vecteur
		void ToString() const;
		
		//Calcule l'angle entre deux vecteurs en degrés
		T Angle(const Vct2D<T>& other) const;

		//limite la magnitude du vecteur à une valeur max
		Vct2D<T> ClampMagnitude(const Vct2D<T>&, T maxLength);

		//Calcule la distance entre deux vecteurs
		T Distance(const Vct2D<T>& other) const;

		//Calcule le produit scalaire entre deux vecteurs
		T Dot(const Vct2D<T>& other) const;

		//Interpole linéairement entre deux vecteurs en fonction de t avec une limite entre 0 et 1
		Vct2D<T> LerpClamp(const Vct2D<T>& target, T t) const;

		//Interpole linéairement entre deux vecteurs en fonction de t sans limite
		Vct2D<T> LerpUnClamp(const Vct2D<T>& target, T t) const;

		//renvoie le vecteur maximum entre deux vecteurs
		Vct2D<T> Max(const Vct2D<T>& other) const;

		//renvoie le vecteur minimum entre deux vecteurs
		Vct2D<T> Min(const Vct2D<T>& other) const;

		//Déplace un vecteur vers une cible
		Vct2D<T> MoveTowards(Vct2D<T> target, T maxDistanceDelta) const;

		//renvoie un vecteur perpendiculaire au vecteur d'origine
		Vct2D<T> Perpendicular(bool Sense = true ) const;

		//Renvoie le vecteur réfléchi par rapport à un vecteur normalisé
		Vct2D<T> Reflect(const Vct2D<T>& vct_normaliser) const;

		//Multiplie chaque composante du vecteur par l'autre vecteur sans modifier le vecteur d'origine
		Vct2D<T> Scale(const Vct2D<T>& other) const;

		T SignedAngle(Vct2D<T>& other) const;

		/*MathsVct3D::Vct3D Transfo3D(Vct2D<T>& vct_transfo) const;*/


				// multiplication par un scalaire
		Vct2D<T> operator*(T scal) const {
			return Vct2D<T>(x * scal, y * scal);
		}


		// Addition de vecteurs
		Vct2D<T> operator+(const Vct2D<T>& other) const {
			return Vct2D<T>(x + other.x, y + other.y);
		}

		// Soustraction de vecteurs
		Vct2D<T> operator-(const Vct2D<T>& other) const {
			return Vct2D<T>(x - other.x, y - other.y);
		}

		// Division par un scalaire
		Vct2D<T> operator/(T scal) const {
			if (scal != 0) {
				return Vct2D<T>(x / scal, y  / scal);
			}
			else {
				throw std::runtime_error("division par 0");
				/*return Vct2D<T>(0, 0);*/ //jamais effectuer a cause de l'exception
			}
		}

		//affiche la position x et y
		T& operator[](int index)
		{
			switch (index)
			{
			case 0:
				return x;

			case 1:
				return y;

			default: throw std::out_of_range("Index invalide");
			}
			
		}
		
	
	};
};
#include "Vec2.inl"