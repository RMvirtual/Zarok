#include <cmath>
#include "gtest/gtest.h"
#include "maths/vector.h"

TEST(MathsVector, ShouldCreateVectorWithTwoElements)
{
    Maths::Vector vector{1, 2};
    EXPECT_EQ(1, vector[0]);
    EXPECT_EQ(2, vector[1]);
}

TEST(MathsVector, ShouldCreateVectorWithThreeElements)
{
    Maths::Vector vector{4, 5, 6};
    EXPECT_EQ(4, vector[0]);
    EXPECT_EQ(5, vector[1]);
    EXPECT_EQ(6, vector[2]);
}

TEST(MathsVector, ShouldCreateVectorWithFourElements)
{
    Maths::Vector vector{1, 2, 3, 4};
    EXPECT_EQ(1, vector[0]);
    EXPECT_EQ(2, vector[1]);
    EXPECT_EQ(3, vector[2]);
    EXPECT_EQ(4, vector[3]);
}

TEST(MathsVector, ShouldCreateVectorWithArray)
{
    double array[]{1, 2, 3};
    Maths::Vector vector{array, 3};

    EXPECT_EQ(1, vector[0]);
    EXPECT_EQ(2, vector[1]);
    EXPECT_EQ(3, vector[2]);
}

TEST(MathsVector, ShouldCreateVectorWithStlVector)
{
    std::vector<double> stlVector{1, 2, 3};
    Maths::Vector vector{stlVector};

    EXPECT_EQ(1, vector[0]);
    EXPECT_EQ(2, vector[1]);
    EXPECT_EQ(3, vector[2]);
}

TEST(MathsVector, ShouldCalculateLength)
{
    Maths::Vector vector{{1, 2, 3, 4, 5}};
    EXPECT_EQ(5, vector.length());
}

TEST(MathsVector, ShouldCalculateMagnitudeWithTwoElements)
{
    Maths::Vector vector{12, -5};
    double magnitude = vector.magnitude();
    double correctMagnitude = 13;

    EXPECT_DOUBLE_EQ(correctMagnitude, magnitude);

    Maths::Vector vectorWithMagnitudeOfSqrt5{1, -2};
    magnitude = vectorWithMagnitudeOfSqrt5.magnitude();
    correctMagnitude = sqrt(5);

    EXPECT_DOUBLE_EQ(correctMagnitude, magnitude);
}

TEST(MathsVector, ShouldCalculateMagnitudeOfThreeElementVector)
{
    Maths::Vector vector1{1, 1, 2};
    Maths::Vector vector2{-4, -8, 6};

    double vector1CorrectMagnitude = 2.4494897427831779;
    double vector2CorrectMagnitude = 10.770329614269007;

    EXPECT_DOUBLE_EQ(vector1.magnitude(), vector1CorrectMagnitude);
    EXPECT_DOUBLE_EQ(vector2.magnitude(), vector2CorrectMagnitude);
}

TEST(MathsVector, ShouldIndexDirectlyWithOperator)
{
    Maths::Vector vector{5, 6};

    EXPECT_DOUBLE_EQ(5, vector[0]);
    EXPECT_DOUBLE_EQ(6, vector[1]);
}

TEST(MathsVector, ShouldAddTwoVectorsWithPositiveValues)
{
    Maths::Vector lhsVector{1, 2, 3, 4};
    Maths::Vector rhsVector{5, 6, 7, 8};

    Maths::Vector resultVector = lhsVector + rhsVector;

    double correctValues[]{6, 8, 10, 12};

    for (int elementNo = 0; elementNo < resultVector.length(); elementNo++)
        EXPECT_DOUBLE_EQ(correctValues[elementNo], resultVector[elementNo]);
}

TEST(MathsVector, ShouldAddTwoVectorsWithMixedSignValues)
{
    Maths::Vector lhsVector{-1, -5, 15, 6};
    Maths::Vector rhsVector{5, 6, -7, 8};
    Maths::Vector resultVector = lhsVector + rhsVector;

    double correctValues[]{4, 1, 8, 14};

    for (int elementNo = 0; elementNo < resultVector.length(); elementNo++)
        EXPECT_DOUBLE_EQ(correctValues[elementNo], resultVector[elementNo]);
}

TEST(MathsVector, ShouldSubtractTwoVectorsWithPositiveValues)
{
    Maths::Vector lhsVector{5, 6, 7, 8};
    Maths::Vector rhsVector{1, 3, 5, 7};

    Maths::Vector resultVector = lhsVector - rhsVector;

    double correctValues[]{4, 3, 2, 1};

    for (int elementNo = 0; elementNo < resultVector.length(); elementNo++)
        EXPECT_DOUBLE_EQ(correctValues[elementNo], resultVector[elementNo]);
}

TEST(MathsVector, ShouldSubtractTwoVectorsWithMixedSignValues)
{
    Maths::Vector lhsVector{-1, -5, 15, 6};
    Maths::Vector rhsVector{5, 6, -7, 8};
    Maths::Vector resultVector = lhsVector - rhsVector;

    double correctValues[]{-6, -11, 22, -2};

    for (int elementNo = 0; elementNo < resultVector.length(); elementNo++)
        EXPECT_DOUBLE_EQ(correctValues[elementNo], resultVector[elementNo]);
}

TEST(MathsVector, ShouldMultiplyVectorWithScalarOnRHS)
{
    Maths::Vector vector{5, 6, 7, -8};
    double scalar = 2;
    Maths::Vector resultVector = vector * scalar;

    double correctValues[]{10, 12, 14, -16};

    for (int elementNo = 0; elementNo < resultVector.length(); elementNo++)
        EXPECT_DOUBLE_EQ(correctValues[elementNo], resultVector[elementNo]);
}

TEST(MathsVector, ShouldMultiplyVectorWithScalarOnLHS)
{
    Maths::Vector vector{5, 6, 7, -8};
    Maths::Vector resultVector = 2 * vector;

    double correctValues[]{10, 12, 14, -16};

    for (int elementNo = 0; elementNo < resultVector.length(); elementNo++)
        EXPECT_DOUBLE_EQ(correctValues[elementNo], resultVector[elementNo]);
}

TEST(MathsVector, ShouldDivideVectorWithAScalar)
{
    Maths::Vector vector{8, 16, 32, -50};
    Maths::Vector resultVector = vector / 2;

    double correctValues[]{4, 8, 16, -25};

    for (int elementNo = 0; elementNo < resultVector.length(); elementNo++)
        EXPECT_DOUBLE_EQ(correctValues[elementNo], resultVector[elementNo]);
}

TEST(MathsVector, DotProductOfVectorsWithPositiveValues)
{
    Maths::Vector lhsVector{1, 2, 3, 4};
    Maths::Vector rhsVector{5, 6, 7, 8};

    double dotProduct = lhsVector * rhsVector;
    double correctDotProduct = 70;

    EXPECT_DOUBLE_EQ(correctDotProduct, dotProduct);
}

TEST(MathsVector, DotProductOfVectorsWithMixedValues)
{
    Maths::Vector lhsVector{-1, -5, 15, 6};
    Maths::Vector rhsVector{5, -6, -7, 8};

    double dotProduct = lhsVector * rhsVector;
    double correctDotProduct = -32;

    EXPECT_DOUBLE_EQ(correctDotProduct, dotProduct);
}

TEST(MathsVector, ShouldCalculateVectorProduct)
{
    Maths::Vector vector1 = {2, 3, 4};
    Maths::Vector vector2 = {5, 6, 7};

    Maths::Vector vectorProduct = vector1.vectorProduct(vector2);
    double correctValues[]{-3, 6, -3};

    int noOfValues = vectorProduct.length();

    for (int i = 0; i < noOfValues; i++)
    {
        double actualValue = vectorProduct[i];
        double correctValue = correctValues[i];

        EXPECT_DOUBLE_EQ(actualValue, correctValue);
    }
}

TEST(MathsVector, ShouldCalculateAngleBetweenTwoVectors)
{
    Maths::Vector vector1{1, 2, 3};
    Maths::Vector vector2{4, 5, 6};

    double angleInRadians = vector1.angle(vector2);
    double correctAngle = 0.22572612855273419;

    EXPECT_DOUBLE_EQ(angleInRadians, correctAngle);
}

TEST(MathsVector, ShouldIterateThroughVector)
{
    std::vector<double> correctValues{1, 2, 3};
    Maths::Vector vector{correctValues};

    std::vector<double> valuesFromIteration{};

    for (auto value : vector)
        valuesFromIteration.push_back(value);

    int numberOfValues = correctValues.size();

    for (int i = 0; i < numberOfValues; i++)
        EXPECT_DOUBLE_EQ(correctValues[i], valuesFromIteration[i]);
}

TEST(MathsVector, ShouldIndexByVariableLetterSubscriptOperator)
{
    double x = 3, y = 4, z = 5, w = 6;
    Maths::Vector vector{x, y, z, w};

    EXPECT_EQ(x, vector["x"]);
    EXPECT_EQ(y, vector["y"]);
    EXPECT_EQ(z, vector["z"]);
    EXPECT_EQ(w, vector["w"]);
}

TEST(MathsVector, ShouldIndexZeroValueByVariableLetterSubscriptOperator)
{
    double x = 0, y = 0, z = 0, w = 0;
    Maths::Vector vector{x, y, z, w};

    EXPECT_EQ(x, vector["x"]);
    EXPECT_EQ(y, vector["y"]);
    EXPECT_EQ(z, vector["z"]);
    EXPECT_EQ(w, vector["w"]);
}