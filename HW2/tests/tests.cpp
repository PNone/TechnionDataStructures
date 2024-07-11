

#include <string>

#include "Matrix.h"
#include "MataMvidia.h"

using namespace std;

typedef bool (*testFunc)(void);

bool testMatrix(std::ostream &out);

bool testMataMvidia(std::ostream &out);

void constructorAssignment(std::ostream &out);

void constructorErrorSize(std::ostream &out);

void constructorErrorSize1(std::ostream &out);

void constructorErrorSize2(std::ostream &out);

void constructorErrorSize3(std::ostream &out);

void constructorErrorSize4(std::ostream &out);

void mataMvidiaE2E(std::ostream &out);

bool testMatrixInitializationAndOperations(std::ostream &out);

bool testMataMvidiaOperations(std::ostream &out);

bool testMatrixTransformations(std::ostream &out);

bool testNonSquareMatrixTransformations(std::ostream &out);


#define ASSERT_TEST(expr)                                                      \
do {                                                                           \
    if (!(expr)) {                                                             \
        std::cout << "\nAssertion failed at ";                                 \
        std::cout << __FILE__ << ":" << __LINE__ << ": " << #expr << std::endl;\
        exit(1);                                                               \
    }                                                                          \
} while (0)


int main(int argc, char **argv) {
    string testName = string(argv[1]);
    if (testName == "example" || testName == "exampleMatrix") {
        testMatrix(std::cout);
    }
    if (testName == "example" || testName == "exampleMataMvidia") {
        testMataMvidia(std::cout);
    }

    if (testName == "constructorAssignment") {
        constructorAssignment(std::cout);
    }
    if (testName == "constructorErrorSize") {
        constructorErrorSize(std::cout);
    }
    if (testName == "constructorErrorSize1") {
        constructorErrorSize1(std::cout);
    }
    if (testName == "constructorErrorSize2") {
        constructorErrorSize2(std::cout);
    }
    if (testName == "constructorErrorSize3") {
        constructorErrorSize3(std::cout);
    }
    if (testName == "constructorErrorSize4") {
        constructorErrorSize4(std::cout);
    }
    if (testName == "mataMvidiaE2E") {
        mataMvidiaE2E(std::cout);
    }
    if (testName == "matrixInit") {
        testMatrixInitializationAndOperations(std::cout);
    }
    if (testName == "mataMvidiaOperations") {
        testMataMvidiaOperations(std::cout);
    }
    if (testName == "matrixTransformations") {
        testMatrixTransformations(std::cout);
    }
    if (testName == "nonSquareMatrixTransformations") {
        testNonSquareMatrixTransformations(std::cout);
    }

    return 0;
}

bool testMatrix(std::ostream &out) {
    Matrix m1(2, 2);
    Matrix m2(2, 2);

    m1(0, 0) = 1;
    m1(0, 1) = 2;
    m1(1, 0) = 3;
    m1(1, 1) = 4;

    m2(0, 0) = 5;
    m2(0, 1) = 6;
    m2(1, 0) = 7;
    m2(1, 1) = 8;

    Matrix m3 = m1 + m2;
    ASSERT_TEST(m3(0, 0) == 6);
    ASSERT_TEST(m3(0, 1) == 8);
    ASSERT_TEST(m3(1, 0) == 10);
    ASSERT_TEST(m3(1, 1) == 12);

    Matrix m4 = m1 * m2;
    m4 *= 1;
    ASSERT_TEST(m4(0, 0) == 19);
    ASSERT_TEST(m4(0, 1) == 22);
    ASSERT_TEST(m4(1, 0) == 43);
    ASSERT_TEST(m4(1, 1) == 50);

    m1 += m2;
    m1 *= m2;
    m1 -= m2;
    m1 = m3 - m2;

    ASSERT_TEST(-m1 == -1 * m1);
    ASSERT_TEST(-m1 == m1 * -1);

    ASSERT_TEST(m2.rotateClockwise().rotateCounterClockwise() == m2);

    ASSERT_TEST(m1.transpose().transpose() == m1);

    out << m2 << std::endl;

    return true;
}

bool testMataMvidia(std::ostream &out) {
    Matrix frame1(2, 2);
    Matrix frame2(2, 2);

    frame1(0, 0) = 1;
    frame1(0, 1) = 2;
    frame1(1, 0) = 3;
    frame1(1, 1) = 4;

    frame2(0, 0) = 5;
    frame2(0, 1) = 6;
    frame2(1, 0) = 7;
    frame2(1, 1) = 8;

    Matrix array[2];
    array[0] = frame1;
    array[1] = frame2;

    MataMvidia movie("MataMatrix", "Adi Harif", array, 2);

    ASSERT_TEST(movie[0] == frame1);

    movie += frame1;

    ASSERT_TEST(movie[2] == frame1);

    Matrix frame01(2, 2);
    Matrix frame11(2, 2);

    frame01(0, 0) = 10;
    frame01(0, 1) = 20;
    frame01(1, 0) = 30;
    frame01(1, 1) = 40;

    frame11(0, 0) = 50;
    frame11(0, 1) = 60;
    frame11(1, 0) = 70;
    frame11(1, 1) = 80;

    Matrix array1[2];
    array1[0] = frame01;
    array1[1] = frame11;

    MataMvidia movie1("MataMatrix and the chamber of secrets", "Adi Harif", array1, 2);

    ASSERT_TEST(movie1[0] == frame01);

    //test output
    out << movie;

    MataMvidia movie2 = movie + movie1;
    movie += movie1;

    return true;
}

void constructorAssignment(std::ostream &out) {
    Matrix a;
    out << a << endl;

    Matrix c(3, 2);
    c(0, 1) = 2;
    Matrix d = c;
    d(1, 1) = c(0, 1);

    a = d;
    out << a << endl;
    out << c << endl;
    out << d << endl;
}

void constructorErrorSize(std::ostream &out) {
    Matrix a;
    out << a << endl;
    //error size
    Matrix b(-1, 0);
}

void constructorErrorSize1(std::ostream &out) {
    Matrix c(3, 2);
    c(0, 1) = 2;

    //error index;
    c(-1, 3) = 2;
}

void constructorErrorSize2(std::ostream &out) {
    Matrix c(3, 2);
    c(0, 1) = 2;
    Matrix d = c;
    d(1, 1) = c(0, 1);

    //error index;
    d(2, 4) = 0;
}

void constructorErrorSize3(std::ostream &out) {
    Matrix c(3, 2);
    c(0, 1) = 2;
    Matrix d = c;
    d(1, 1) = c(0, 1);

    //error index;
    d(2, 4);
}

void constructorErrorSize4(std::ostream &out) {
    Matrix c(3, 2);
    c(0, 1) = 2;

    //error index;
    c(-1, 3);
}

void mataMvidiaE2E(std::ostream &out) {
    Matrix a(3, 3);
    a(0, 0) = 1;
    a(0, 1) = 2;
    a(0, 2) = 3;
    a(1, 0) = 0;
    a(1, 1) = 2;
    a(1, 2) = 0;
    a(2, 0) = 1;
    a(2, 1) = 4;
    a(2, 2) = 1;

    out << "a:" << endl << a << endl;

    Matrix b = a.transpose() - a;
    out << "a.transpose()-a:" << endl << b << endl;

    Matrix c = a.rotateCounterClockwise() + b.rotateClockwise();
    out << "a.rotateCounterClockwise()+b.rotateClockwise()" << endl << c
        << endl;

    Matrix d(2, 3);
    d(0, 0) = 1;
    d(0, 1) = 0;
    d(0, 2) = 2;
    d(1, 0) = 3;
    d(1, 1) = 1;
    d(1, 2) = 0;

    out << "d:" << endl << d << endl;

    Matrix e = d.rotateCounterClockwise();
    out << "e:" << endl << e << endl;


    out << "a*e:" << endl << a * e << endl;
    out << "d*a:" << endl << d * a << endl;
    out << "a+b:" << endl << a + b << endl;

    out << "-a" << endl << -a << endl;
    out << "2*d:" << endl << 2 * d << endl;
    out << "2*d==d*2:" << endl << (2 * d == d * 2) << endl;
    out << "a.transpose!=a.counterClockSize:" << endl
        << (a.transpose() != a.rotateCounterClockwise()) << endl;

    Matrix array[5];
    array[0] = a;
    array[1] = b;
    array[2] = c;
    array[3] = d;
    array[4] = e;
    MataMvidia m("Matrix", "linoy", array, 5);
    out << "m" << endl << m << endl;
    MataMvidia z = m;
    out << "z" << endl << z << endl;
    MataMvidia x("malibu", "adi", array + 2, 3);
    z = x;
    out << "z" << endl << z << endl;
    //-d
    m[1] = (-m[1]);
    out << "m[1]= -b" << endl << m[1] << endl;
    out << "m+x" << endl << m + x << endl;
    out << "m+=a*e" << endl << (m += (a * e)) << endl;
    out << "m+=x" << endl << (m += x) << endl;
    out << "m" << endl << m << endl;
}

/**
 * Test matrix initialization and basic operations
 * @param out
 * @return
 */
bool testMatrixInitializationAndOperations(std::ostream &out) {
    Matrix m1(2, 2), m2(2, 2), m3;
    m1(0, 0) = 1;
    m1(0, 1) = 2;
    m1(1, 0) = 3;
    m1(1, 1) = 4;
    m2(0, 0) = 5;
    m2(0, 1) = 6;
    m2(1, 0) = 7;
    m2(1, 1) = 8;

    out << m1 << endl;
    out << m2 << endl;

    // Test addition

    m3 = m1 + m2;
    out << m3 << endl;
    ASSERT_TEST(m3(0, 0) == 6 && m3(0, 1) == 8 && m3(1, 0) == 10 && m3(1, 1) == 12);

    // Test multiplication by scalar
    m3 = m1 * 3;
    out << m3 << endl;
    ASSERT_TEST(m3(0, 0) == 3 && m3(0, 1) == 6 && m3(1, 0) == 9 && m3(1, 1) == 12);

    // Test transpose
    m3 = m1.transpose();
    out << m3 << endl;
    ASSERT_TEST(m3(0, 0) == 1 && m3(0, 1) == 3 && m3(1, 0) == 2 && m3(1, 1) == 4);

    // Test rotation
    m3 = m1.rotateClockwise();
    out << m3 << endl;
    ASSERT_TEST(m3(0, 0) == 3 && m3(0, 1) == 1 && m3(1, 0) == 4 && m3(1, 1) == 2);

    return true;
}

/**
 * Test MataMvidia movie operations
 * @param out
 * @return
 */
bool testMataMvidiaOperations(std::ostream &out) {
    Matrix frame1(2, 2), frame2(2, 2);
    frame1(0, 0) = 1;
    frame1(0, 1) = 2;
    frame1(1, 0) = 3;
    frame1(1, 1) = 4;
    frame2(0, 0) = 5;
    frame2(0, 1) = 6;
    frame2(1, 0) = 7;
    frame2(1, 1) = 8;

    Matrix frames[] = {frame1, frame2};
    MataMvidia movie("Test Movie", "Author", frames, 2);

    // Test movie indexing
    out << "First index is first frame: " << (movie[0] == frame1) << endl;
    out << "Second index is second frame: " << (movie[1] == frame2) << endl;
    ASSERT_TEST(movie[0] == frame1 && movie[1] == frame2);

    // Test addition of frame
    movie += frame1;
    out << "Third index is third frame: " << (movie[2] == frame1) << endl;
    ASSERT_TEST(movie[2] == frame1);

    out << endl << movie;

    return true;
}

/**
 * Create matrices of various sizes
 * @param out
 * @return
 */
bool testMatrixTransformations(std::ostream &out) {
    Matrix m1(3, 3), m2(1, 4), m3(4, 1);
    // Initialize m1 as a 3x3 matrix
    m1(0, 0) = 1;
    m1(0, 1) = 2;
    m1(0, 2) = 3;
    m1(1, 0) = 4;
    m1(1, 1) = 5;
    m1(1, 2) = 6;
    m1(2, 0) = 7;
    m1(2, 1) = 8;
    m1(2, 2) = 9;
    // Initialize m2 as a 1x4 matrix
    m2(0, 0) = 1;
    m2(0, 1) = 2;
    m2(0, 2) = 3;
    m2(0, 3) = 4;
    // Initialize m3 as a 4x1 matrix
    m3(0, 0) = 1;
    m3(1, 0) = 2;
    m3(2, 0) = 3;
    m3(3, 0) = 4;

    out << m1 << endl;
    out << m2 << endl;
    out << m3 << endl;

    // Test transpose functionality
    Matrix mt1 = m1.transpose();
    out << mt1 << endl;
    ASSERT_TEST(mt1(0, 0) == 1 && mt1(1, 0) == 2 && mt1(2, 0) == 3);
    ASSERT_TEST(mt1(0, 1) == 4 && mt1(1, 1) == 5 && mt1(2, 1) == 6);
    ASSERT_TEST(mt1(0, 2) == 7 && mt1(1, 2) == 8 && mt1(2, 2) == 9);

    Matrix mt2 = m2.transpose();
    out << mt2 << endl;
    ASSERT_TEST(mt2(0, 0) == 1 && mt2(1, 0) == 2 && mt2(2, 0) == 3 && mt2(3, 0) == 4);

    Matrix mt3 = m3.transpose();
    out << mt3 << endl;
    ASSERT_TEST(mt3(0, 0) == 1 && mt3(0, 1) == 2 && mt3(0, 2) == 3 && mt3(0, 3) == 4);

    // Test rotation clockwise
    Matrix mcw1 = m1.rotateClockwise();
    out << mcw1 << endl;
    ASSERT_TEST(mcw1(0, 0) == 7 && mcw1(0, 1) == 4 && mcw1(0, 2) == 1);
    ASSERT_TEST(mcw1(1, 0) == 8 && mcw1(1, 1) == 5 && mcw1(1, 2) == 2);
    ASSERT_TEST(mcw1(2, 0) == 9 && mcw1(2, 1) == 6 && mcw1(2, 2) == 3);

    // Test rotation counterclockwise
    Matrix mccw1 = m1.rotateCounterClockwise();
    out << mccw1 << endl;
    ASSERT_TEST(mccw1(0, 0) == 3 && mccw1(0, 1) == 6 && mccw1(0, 2) == 9);
    ASSERT_TEST(mccw1(1, 0) == 2 && mccw1(1, 1) == 5 && mccw1(1, 2) == 8);
    ASSERT_TEST(mccw1(2, 0) == 1 && mccw1(2, 1) == 4 && mccw1(2, 2) == 7);

    // Test identity rotations
    Matrix mid = m1.rotateClockwise().rotateCounterClockwise();
    out << mid << endl;
    ASSERT_TEST(mid == m1);

    Matrix mid2 = m1.rotateCounterClockwise().rotateClockwise();
    out << mid2 << endl;
    ASSERT_TEST(mid2 == m1);

    // Test consecutive rotations
    Matrix m4x4(4, 4); // Create a 4x4 matrix for testing multiple rotations
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m4x4(i, j) = i * 4 + j + 1;
        }
    }
    out << m4x4 << endl;
    Matrix r90 = m4x4.rotateClockwise();
    out << r90 << endl;
    Matrix r180 = r90.rotateClockwise();
    out << r180 << endl;
    Matrix r270 = r180.rotateClockwise();
    out << r270 << endl;
    Matrix r360 = r270.rotateClockwise();
    out << r360 << endl;
    ASSERT_TEST(r360 == m4x4);

    out << m4x4.transpose().transpose() << endl;
    // Ensure transpose of transpose is original
    ASSERT_TEST(m4x4.transpose().transpose() == m4x4);

    return true;
}

/**
 * Create non-square matrices
 * @param out
 * @return
 */
bool testNonSquareMatrixTransformations(std::ostream &out) {
    Matrix m1(2, 3), m2(3, 2);

    // Initialize m1 as a 2x3 matrix
    m1(0, 0) = 1;
    m1(0, 1) = 2;
    m1(0, 2) = 3;
    m1(1, 0) = 4;
    m1(1, 1) = 5;
    m1(1, 2) = 6;

    // Initialize m2 as a 3x2 matrix
    m2(0, 0) = 1;
    m2(0, 1) = 2;
    m2(1, 0) = 3;
    m2(1, 1) = 4;
    m2(2, 0) = 5;
    m2(2, 1) = 6;

    out << m1 << endl;
    out << m2 << endl;

    // Test transpose functionality
    Matrix mt1 = m1.transpose();
    out << mt1 << endl;
    ASSERT_TEST(mt1(0, 0) == 1 && mt1(1, 0) == 2 && mt1(2, 0) == 3);
    ASSERT_TEST(mt1(0, 1) == 4 && mt1(1, 1) == 5 && mt1(2, 1) == 6);

    Matrix mt2 = m2.transpose();
    out << mt2 << endl;
    ASSERT_TEST(mt2(0, 0) == 1 && mt2(0, 1) == 3 && mt2(0, 2) == 5);
    ASSERT_TEST(mt2(1, 0) == 2 && mt2(1, 1) == 4 && mt2(1, 2) == 6);

    // Test scalar multiplication
    Matrix ms1 = m1 * 2;
    out << ms1 << endl;
    ASSERT_TEST(ms1(0, 0) == 2 && ms1(0, 1) == 4 && ms1(0, 2) == 6);
    ASSERT_TEST(ms1(1, 0) == 8 && ms1(1, 1) == 10 && ms1(1, 2) == 12);
    // Test scalar *=
    ms1 *= 3;
    out << ms1 << endl;

    // Test scalar multiply from the left
    Matrix msl1 = 2 * m1;
    out << msl1 << endl;

    Matrix ms2 = m2 * 3;
    out << ms2 << endl;
    ASSERT_TEST(ms2(0, 0) == 3 && ms2(0, 1) == 6);
    ASSERT_TEST(ms2(1, 0) == 9 && ms2(1, 1) == 12);
    ASSERT_TEST(ms2(2, 0) == 15 && ms2(2, 1) == 18);

    // Test scalar *=
    ms2 *= 4;
    out << ms2 << endl;

    // Test scalar multiply from the left
    Matrix msl2 = 3 * m2;
    out << msl2 << endl;

    // Test the transpose of the transpose returns the original matrix
    ASSERT_TEST(m1.transpose().transpose() == m1);
    ASSERT_TEST(m2.transpose().transpose() == m2);
    out << m1.transpose().transpose() << endl;
    out << m2.transpose().transpose() << endl;

    // Ensure transposing multiple times toggles between the two configurations
    ASSERT_TEST(m1.transpose().transpose().transpose() == m1.transpose());
    ASSERT_TEST(m2.transpose().transpose().transpose() == m2.transpose());
    out << m1.transpose().transpose().transpose() << endl;
    out << m1.transpose() << endl;
    out << m2.transpose().transpose().transpose() << endl;
    out << m2.transpose() << endl;

    return true;
}

