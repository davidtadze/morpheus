#include <cmath>
#include <iostream>

#include <math/Matrix3.hpp>
#include <math/Vector3.hpp>

#include "gtest/gtest.h"

TEST(MathTest, VectorGet) {
    morpheus::Vector3 v1;

    EXPECT_TRUE(v1.x() == 0 && v1.y() == 0 && v1.z() == 0);

    float x = 1.0F;
    float y = 2.0F;
    float z = 3.0F;
    morpheus::Vector3 v2(x, y, z);

    EXPECT_TRUE(v2.x() == x && v2.y() == y && v2.z() == z);
    EXPECT_TRUE(v2[0] == x && v2[1] == y && v2[2] == z);
}

TEST(MathTest, VectorAddition) {
    float ax = 1.0F;
    float ay = 2.0F;
    float az = 3.0F;
    morpheus::Vector3 a(ax, ay, az);

    float bx = 4.0F;
    float by = 5.0F;
    float bz = 6.0F;
    morpheus::Vector3 b(bx, by, bz);

    float cx = 7.0F;
    float cy = 8.0F;
    float cz = 9.0F;
    morpheus::Vector3 c(cx, cy, cz);

    float eps = 0.001F;

    morpheus::Vector3 lsum1 = (a + b) + c;
    morpheus::Vector3 rsum1 = a + (b + c);

    EXPECT_TRUE(   abs(lsum1.x() - rsum1.x()) < eps && abs(lsum1.x() - (ax + bx + cx)) < eps
                && abs(lsum1.y() - rsum1.y()) < eps && abs(lsum1.y() - (ay + by + cy)) < eps
                && abs(lsum1.z() - rsum1.z()) < eps && abs(lsum1.z() - (az + bz + cz)) < eps);

    morpheus::Vector3 lsum2 = a + b;
    morpheus::Vector3 rsum2 = b + a;

    EXPECT_TRUE(   abs(lsum2.x() - rsum2.x()) < eps && abs(lsum2.x() - (ax + bx)) < eps
                && abs(lsum2.y() - rsum2.y()) < eps && abs(lsum2.y() - (ay + by)) < eps
                && abs(lsum2.z() - rsum2.z()) < eps && abs(lsum2.z() - (az + bz)) < eps);

    a += b;

    EXPECT_TRUE(   abs(a.x() - (ax + bx)) < eps 
                && abs(a.y() - (ay + by)) < eps 
                && abs(a.z() - (az + bz)) < eps);

    b -= c;

    EXPECT_TRUE(   abs(b.x() - (bx - cx)) < eps 
                && abs(b.y() - (by - cy)) < eps 
                && abs(b.z() - (bz - cz)) < eps);
}

TEST(MathTest, VectorScalarMultiplication) {
    float ax = 1.0F;
    float ay = 2.0F;
    float az = 3.0F;
    morpheus::Vector3 a(ax, ay, az);

    float bx = 4.0F;
    float by = 5.0F;
    float bz = 6.0F;
    morpheus::Vector3 b(bx, by, bz);

    float cx = 7.0F;
    float cy = 8.0F;
    float cz = 9.0F;
    morpheus::Vector3 c(cx, cy, cz);

    float eps = 0.001F;
    
    float s = 2.0F;
    float t = 3.0F;

    morpheus::Vector3 lproduct1 = a * (s * t);
    morpheus::Vector3 rproduct1 = (a * s) * t;

    EXPECT_TRUE(   abs(lproduct1.x() - rproduct1.x()) < eps && abs(lproduct1.x() - s * t * ax) < eps
                && abs(lproduct1.y() - rproduct1.y()) < eps && abs(lproduct1.y() - s * t * ay) < eps
                && abs(lproduct1.z() - rproduct1.z()) < eps && abs(lproduct1.z() - s * t * az) < eps);
    
    morpheus::Vector3 lproduct2 = (a + b) * s;
    morpheus::Vector3 rproduct2 = b * s + a * s;

    EXPECT_TRUE(   abs(lproduct2.x() - rproduct2.x()) < eps && abs(lproduct2.x() - s * (ax + bx)) < eps
                && abs(lproduct2.y() - rproduct2.y()) < eps && abs(lproduct2.y() - s * (ay + by)) < eps
                && abs(lproduct2.z() - rproduct2.z()) < eps && abs(lproduct2.z() - s * (az + bz)) < eps);

    morpheus::Vector3 lproduct3 = a * (s + t);
    morpheus::Vector3 rproduct3 = a * s + a * t;

    EXPECT_TRUE(   abs(lproduct3.x() - rproduct3.x()) < eps && abs(lproduct3.x() - (s + t) * ax) < eps
                && abs(lproduct3.y() - rproduct3.y()) < eps && abs(lproduct3.y() - (s + t) * ay) < eps
                && abs(lproduct3.z() - rproduct3.z()) < eps && abs(lproduct3.z() - (s + t) * az) < eps);
}

TEST(MathTest, VectorMultiplication) {
    float ax = 1.0F;
    float ay = 2.0F;
    float az = 3.0F;
    morpheus::Vector3 a(ax, ay, az);

    float bx = 4.0F;
    float by = 5.0F;
    float bz = 6.0F;
    morpheus::Vector3 b(bx, by, bz);

    float eps = 0.001F;

    float dot1 = morpheus::dot(a, b);
    float dot2 = a.dot(b);

    EXPECT_TRUE(   abs(dot1 - (ax * bx + ay * by + az * bz)) < eps
                && abs(dot2 - (ax * bx + ay * by + az * bz)) < eps);

    morpheus::Vector3 cross = morpheus::cross(a, b);

    EXPECT_TRUE(   abs(cross[0] + 3.0F) < eps
                && abs(cross[1] - 6.0F) < eps
                && abs(cross[2] + 3.0F) < eps);

    float magnitude = morpheus::magnitude(a);

    EXPECT_TRUE(   abs(magnitude - sqrt(ax * ax + ay * ay + az * az)) < eps
                && abs(magnitude - sqrt(a.dot(a))) < eps
                && abs(magnitude - sqrt(morpheus::dot(a, a))) < eps);

    morpheus::Vector3 normalized = morpheus::normalize(a);

    EXPECT_TRUE(abs(normalized.magnitude() - 1.0F) < eps);
}

TEST(MathTest, MatrixGet) {
  float n00 = 0.0F; float n01 = 1.0F; float n02 = 2.0F;
  float n10 = 3.0F; float n11 = 4.0F; float n12 = 5.0F;
  float n20 = 6.0F; float n21 = 7.0F; float n22 = 8.0F;

  morpheus::Matrix3 m = {
    { n00, n01, n02 },
    { n10, n11, n12 },
    { n20, n21, n22 }
  };

  EXPECT_TRUE(   m(0, 0) == n00 && m(0, 1) == n01 && m(0, 2) == n02
              && m(1, 0) == n10 && m(1, 1) == n11 && m(1, 2) == n12
              && m(2, 0) == n20 && m(2, 1) == n21 && m(2, 2) == n22);

  morpheus::Vector3 a(n00, n10, n20);
  morpheus::Vector3 b(n01, n11, n21);
  morpheus::Vector3 c(n02, n12, n22);

  EXPECT_TRUE(   m[0].x() == n00 && m[1].x() == n01 && m[2].x() == n02
              && m[0].y() == n10 && m[1].y() == n11 && m[2].y() == n12
              && m[0].z() == n20 && m[1].z() == n21 && m[2].z() == n22);
}

TEST(MathTest, MatrixMultiplication) {
  float n00 = 0.0F; float n01 = 1.0F; float n02 = 2.0F;
  float n10 = 3.0F; float n11 = 4.0F; float n12 = 5.0F;
  float n20 = 6.0F; float n21 = 7.0F; float n22 = 8.0F;

  morpheus::Matrix3 a = {
    { n00, n01, n02 },
    { n10, n11, n12 },
    { n20, n21, n22 }
  };

  morpheus::Matrix3 b = {
    { n00, n01, n02 },
    { n10, n11, n12 },
    { n20, n21, n22 }
  };

  float eps = 0.001F;

  morpheus::Matrix3 m1 = a * b;

  EXPECT_TRUE(   abs(m1(0, 0) - 15.0F) < eps && abs(m1(0, 1) - 18.0F) < eps && abs(m1(0, 2) - 21.0F  ) < eps
              && abs(m1(1, 0) - 42.0F) < eps && abs(m1(1, 1) - 54.0F) < eps && abs(m1(1, 2) - 66.0F  ) < eps
              && abs(m1(2, 0) - 69.0F) < eps && abs(m1(2, 1) - 90.0F) < eps && abs(m1(2, 2) - 111.0F ) < eps);
  
  a *= b;

  EXPECT_TRUE(   abs(a(0, 0) - 15.0F) < eps && abs(a(0, 1) - 18.0F) < eps && abs(a(0, 2) - 21.0F  ) < eps
              && abs(a(1, 0) - 42.0F) < eps && abs(a(1, 1) - 54.0F) < eps && abs(a(1, 2) - 66.0F  ) < eps
              && abs(a(2, 0) - 69.0F) < eps && abs(a(2, 1) - 90.0F) < eps && abs(a(2, 2) - 111.0F ) < eps);

  morpheus::Vector3 c(n00, n01, n02);

  morpheus::Vector3 v1 = a * c;

  EXPECT_TRUE(   abs(v1[0] - 5.0F) < eps 
              && abs(v1[1] - 14.0F) < eps 
              && abs(v1[2] - 23.0F) < eps);
}