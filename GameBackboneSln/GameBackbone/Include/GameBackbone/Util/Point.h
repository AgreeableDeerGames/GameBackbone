#pragma once

#include <GameBackbone/Util/DllUtil.h>

namespace GB {

	/// <summary> Stores a two dimensional position. </summary>
	template<class T>
	struct libGameBackbone Point2D {
	public:
		T x;
		T y;
	};

	template <class T>
	bool operator== (const Point2D<T>& lhs, const Point2D<T>& rhs){
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}

	template <class T>
	bool operator!= (const Point2D<T>& lhs, const Point2D<T>& rhs){
		return !(lhs == rhs);
	}

	template <class T>
	bool operator<  (const Point2D<T>& lhs, const Point2D<T>& rhs){
		return lhs.x<rhs.x || (!(rhs.x<lhs.x) && lhs.y<rhs.y);
	}

	template <class T>
	bool operator<= (const Point2D<T>& lhs, const Point2D<T>& rhs){
		return !(rhs<lhs);
	}

	template <class T>
	bool operator>  (const Point2D<T>& lhs, const Point2D<T>& rhs){
		return rhs<lhs;
	}

	template <class T>
	bool operator>= (const Point2D<T>& lhs, const Point2D<T>& rhs){
		return !(lhs<rhs);
	}





	/// <summary> Stores a three dimensional position. </summary>
	template<class T>
	struct libGameBackbone Point3D {
	public:
		T x;
		T y;
		T z;
	};

	template <class T>
	bool operator== (const Point3D<T>& lhs, const Point3D<T>& rhs) {
		return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
	}

	template <class T>
	bool operator!= (const Point3D<T>& lhs, const Point3D<T>& rhs) {
		return !(lhs == rhs);
	}

	template <class T>
	bool operator<  (const Point3D<T>& lhs, const Point3D<T>& rhs) {
		return lhs.x<rhs.x || (!(rhs.x<lhs.x) && lhs.y<rhs.y) || (!(rhs.x<lhs.x) && !(lhs.y<rhs.y) && lhs.z<rhs.z);
	}

	template <class T>
	bool operator<= (const Point3D<T>& lhs, const Point3D<T>& rhs) {
		return !(rhs<lhs);
	}

	template <class T>
	bool operator>  (const Point3D<T>& lhs, const Point3D<T>& rhs) {
		return rhs<lhs;
	}

	template <class T>
	bool operator>= (const Point3D<T>& lhs, const Point3D<T>& rhs) {
		return !(lhs<rhs);
	}
}
