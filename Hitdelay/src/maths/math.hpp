#include <string>
#include <cstdint>
#include <cmath>

#ifndef MATH_HPP
#define MATH_HPP

namespace utils {

    namespace math {
        template<class T>
        class vec2 {
        public:
            constexpr inline vec2(const T& x = 0, const T& y = 0) noexcept : x(x), y(y) {}

            constexpr inline bool operator==(const vec2<T>& other) const noexcept { return x == other.x && y == other.y; }
            constexpr inline bool operator!=(const vec2<T>& other) const noexcept { return x != other.x || y != other.y; }

            constexpr inline vec2<T> operator+(const vec2<T>& other) noexcept { return vec2<T>(x + other.x, y + other.y); }
            constexpr inline vec2<T> operator-(const vec2<T>& other) noexcept { return vec2<T>(x - other.x, y - other.y); }
            constexpr inline vec2<T> operator/(const vec2<T>& other) noexcept { return vec2<T>(x / other.x, y / other.y); }
            constexpr inline vec2<T> operator*(const vec2<T>& other) noexcept { return vec2<T>(x * other.x, y * other.y); }

            inline operator std::string() const noexcept {
                if constexpr (std::is_convertible_v<T, std::string>) {
                    return "x -> " + static_cast<std::string>(x) +
                        ", y -> " + static_cast<std::string>(y);
                }
                else {
                    return "x -> " + std::to_string(x) +
                        ", y -> " + std::to_string(y);
                }
            }

            T x, y;
        };

        template<class T>
        class vec3 {
        public:
            constexpr inline vec3(const T& x = 0, const T& y = 0, const T& z = 0)
                noexcept : x(x), y(y), z(z) {}

            constexpr inline bool operator==(const vec3<T>& other) const noexcept { return x == other.x && y == other.y && z == other.z; }
            constexpr inline bool operator!=(const vec3<T>& other) const noexcept { return x != other.x || y != other.y || other.z; }

            constexpr inline vec3<T> operator+(const vec3<T>& other) noexcept { return vec3<T>(x + other.x, y + other.y, z + other.z); }
            constexpr inline vec3<T> operator-(const vec3<T>& other) noexcept { return vec3<T>(x - other.x, y - other.y, z - other.z); }
            constexpr inline vec3<T> operator/(const vec3<T>& other) noexcept { return vec3<T>(x / other.x, y / other.y, z / other.z); }
            constexpr inline vec3<T> operator*(const vec3<T>& other) noexcept { return vec3<T>(x * other.x, y * other.y, z * other.z); }

            inline double distance() { return std::sqrt(x * x + y * y + z * z); }
            inline double distance(vec3<T>& v) { return sqrt((x - v.x) * (x - v.x) + (y - v.y) * (y - v.y) + (z - v.z) * (z - v.z)); }
            inline double length() const {
                return std::sqrt(x * x + y * y + z * z);
            }
            float dot(const vec3<T>& v) const {
                return x * v.x + y * v.y + z * v.z;
            }
            inline vec3<T> cross(vec3<T>& v) const {
                return
                {
                        y * v.z - z * v.y,
                        z * v.x - x * v.z,
                        x * v.y - y * v.x
                };
            }

            static vec3<T> normalize(const vec3<T>& v)
            {
                float length = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
                if (length > 0.0f)
                {
                    float invLength = 1.0f / length;
                    return { v.x * invLength, v.y * invLength, v.z * invLength };
                }
                else
                {
                    return { 0.0f, 0.0f, 0.0f };
                }
            }
            inline operator std::string() const noexcept {
                if constexpr (std::is_convertible_v<T, std::string>) {
                    return "x -> " + static_cast<std::string>(x) +
                        ", y -> " + static_cast<std::string>(y) +
                        ", z -> " + static_cast<std::string>(z);
                }
                else {
                    return "x -> " + std::to_string(x) +
                        ", y -> " + std::to_string(y) +
                        ", z -> " + std::to_string(z);
                }
            }

            T x, y, z;
        };

        template<class T>
        class vec4 {
        public:
            constexpr inline vec4(const T& x = 0, const T& y = 0, const T& z = 0, const T& w = 0)
                noexcept : x(x), y(y), z(z), w(w) {}

            constexpr inline bool operator==(const vec4<T>& other) const noexcept { return x == other.x && y == other.y && z == other.z && w == other.w; }
            constexpr inline bool operator!=(const vec4<T>& other) const noexcept { return x != other.x || y != other.y || other.z || other.w; }

            constexpr inline vec4<T> operator+(const vec4<T>& other) noexcept { return vec4<T>(x + other.x, y + other.y, z + other.z, w + other.w); }
            constexpr inline vec4<T> operator-(const vec4<T>& other) noexcept { return vec4<T>(x - other.x, y - other.y, z - other.z, w - other.w); }
            constexpr inline vec4<T> operator/(const vec4<T>& other) noexcept { return vec4<T>(x / other.x, y / other.y, z / other.z, w / other.w); }
            constexpr inline vec4<T> operator*(const vec4<T>& other) noexcept { return vec4<T>(x * other.x, y * other.y, z * other.z, w * other.w); }

            inline operator std::string() const noexcept {
                if constexpr (std::is_convertible_v<T, std::string>) {
                    return "x -> " + static_cast<std::string>(x) +
                        ", y -> " + static_cast<std::string>(y) +
                        ", z -> " + static_cast<std::string>(z) +
                        ", w -> " + static_cast<std::string>(w);
                }
                else {
                    return "x -> " + std::to_string(x) +
                        ", y -> " + std::to_string(y) +
                        ", z -> " + std::to_string(z) +
                        ", w -> " + std::to_string(w);
                }
            }

            T x, y, z, w;
        };

        template <typename T>
        T distance(const vec2<T>& a, const vec2<T>& b) {
            return T(std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2)));
        }

        template <typename T>
        T manhattan_heuristic(const vec2<T>& a, const vec2<T>& b) {
            return T(std::abs(a.x - b.x) + std::abs(a.y - b.y));
        }

        template <typename T>
        T euclidean_heuristic(const vec2<T>& a, const vec2<T>& b) {
            return distance<T>(a, b);
        }

        inline float mod360(float angle)
        {
            while (angle <= -180.0f)
                angle += 360.0f;
            while (angle > 180.0f)
                angle -= 360.0f;
            return angle;
        }

        inline constexpr double pi = 3.14159265;

        inline constexpr std::floating_point auto to_radians(std::floating_point auto angle)
        {
            constexpr double coef = pi / 180.0;
            return angle * coef;
        }
        inline vec2<double> get_yaw_pitch(vec3<double> playerPos, vec3<double> facingPos) {
            vec3<double> delta = facingPos - playerPos;

            double hypxz = std::sqrt(delta.x * delta.x + delta.z * delta.z);

            double pitchRad = std::atan(-delta.y / hypxz);

            double yawDeg = 0.0;
            double pitchDeg = pitchRad * (180.0 / pi);

            if (delta.x != 0.0)
            {
                double yawRad = std::atan2(delta.z, delta.x) - pi / 2;
                yawDeg = yawRad * (180.0 / pi);
            }

            return vec2<double>(yawDeg, pitchDeg);
        }

        inline vec3<double> get_camera_vector(vec2<double> cameraRot, double distance = 1.0) {
            double yawRad = cameraRot.x * (pi / 180.0);
            double pitchRad = cameraRot.y * (pi / 180.0);
            const double hypxz = distance * std::cos(pitchRad);

            return vec3<double>(-std::sin(yawRad) * hypxz, -std::sin(pitchRad) * distance, std::cos(yawRad) * hypxz);
        }

        inline double crop_angle_180(double angle) {
            while (angle <= -180.0) angle += 360.0;
            while (angle > 180.0) angle -= 360.0;
            return angle;
        }

        inline double crop_angle_360(double angle) {
            while (angle < 0.0) angle += 360.0;
            while (angle >= 360.0) angle -= 360.0;
            return angle;
        }


        struct angles
        {
            vec3<double> get_vector() const
            {
                double yaw_rad = utils::math::to_radians(yaw);
                double pitch_rad = utils::math::to_radians(pitch);

                double cos_pitch = std::cos(pitch_rad);
                return { -std::sin(yaw_rad) * cos_pitch, -std::sin(pitch_rad), std::cos(yaw_rad) * cos_pitch };
            }

            angles mod_360() const
            {
                return angles(utils::math::mod360(yaw), utils::math::mod360(pitch));
            }

            angles operator-(const angles& other) const
            {
                return angles(yaw - other.yaw, pitch - other.pitch);
            }

            angles operator+(const angles& other) const
            {
                return angles(yaw + other.yaw, pitch + other.pitch);
            }

            angles operator*(float coefficient) const
            {
                return angles(yaw * coefficient, pitch * coefficient);
            }

            float yaw = 0.f, pitch = 0.f;
        };
    }

}

using vec2i = utils::math::vec2<int>;
using vec2f = utils::math::vec2<float>;
using vec2d = utils::math::vec2<double>;

using vec3i = utils::math::vec3<int>;
using vec3f = utils::math::vec3<float>;
using vec3d = utils::math::vec3<double>;

using vec4i = utils::math::vec4<int>;
using vec4f = utils::math::vec4<float>;

#endif