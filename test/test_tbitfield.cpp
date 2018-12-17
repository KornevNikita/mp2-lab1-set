#include "tbitfield.h"

#include <gtest.h>

TEST(TBitField, can_create_bitfield_with_positive_length)
{
  ASSERT_NO_THROW(TBitField bf(3));
}

TEST(TBitField, can_get_length)
{
  TBitField bf(3);

  EXPECT_EQ(3, bf.getLength());
}

TEST(TBitField, new_bitfield_is_set_to_zero)
{
  TBitField bf(100);

  int sum = 0;
  for (int i = 0; i < bf.getLength(); i++)
  {
    sum += bf.getBit(i);
  }

  EXPECT_EQ(0, sum);
}

TEST(TBitField, can_set_bit)
{
  TBitField bf(10);

  EXPECT_EQ(0, bf.getBit(3));

  bf.setBit(3);
  EXPECT_NE(0, bf.getBit(3));
}

TEST(TBitField, can_clear_bit)
{
  TBitField bf(10);

  int bitIdx = 3;

  bf.setBit(bitIdx);
  EXPECT_NE(0, bf.getBit(bitIdx));

  bf.clrBit(bitIdx);
  EXPECT_EQ(0, bf.getBit(bitIdx));
}

TEST(TBitField, throws_when_create_bitfield_with_negative_length)
{
  ASSERT_ANY_THROW(TBitField bf(-3));
}

TEST(TBitField, throws_when_set_bit_with_negative_index)
{
  TBitField bf(10);

  ASSERT_ANY_THROW(bf.setBit(-3));
}

TEST(TBitField, throws_when_set_bit_with_too_large_index)
{
  TBitField bf(10);

  ASSERT_ANY_THROW(bf.setBit(11));
}

TEST(TBitField, throws_when_get_bit_with_negative_index)
{
  TBitField bf(10);

  ASSERT_ANY_THROW(bf.getBit(-3));
}

TEST(TBitField, throws_when_get_bit_with_too_large_index)
{
  TBitField bf(10);

  ASSERT_ANY_THROW(bf.getBit(11));
}

TEST(TBitField, throws_when_clear_bit_with_negative_index)
{
  TBitField bf(10);

  ASSERT_ANY_THROW(bf.clrBit(-3));
}

TEST(TBitField, throws_when_clear_bit_with_too_large_index)
{
  TBitField bf(10);

  ASSERT_ANY_THROW(bf.clrBit(11));
}

TEST(TBitField, can_assign_bitfields_of_equal_size)
{
  const int size = 2;
  TBitField bf1(size), bf2(size);
  for (int i = 0; i < size; i++)
  {
    bf1.setBit(i);
  }
  bf2 = bf1;

  EXPECT_NE(0, bf2.getBit(0));
  EXPECT_NE(0, bf2.getBit(1));
}

TEST(TBitField, assign_operator_changes_bitfield_size)
{
  const int size1 = 2, size2 = 5;
  TBitField bf1(size1), bf2(size2);
  for (int i = 0; i < size1; i++)
  {
    bf1.setBit(i);
  }
  bf2 = bf1;

  EXPECT_EQ(2, bf2.getLength());
}

TEST(TBitField, can_assign_bitfields_of_non_equal_size)
{
  const int size1 = 2, size2 = 5;
  TBitField bf1(size1), bf2(size2);
  for (int i = 0; i < size1; i++)
  {
    bf1.setBit(i);
  }
  bf2 = bf1;

  EXPECT_NE(0, bf2.getBit(0));
  EXPECT_NE(0, bf2.getBit(1));
}

TEST(TBitField, compare_equal_bitfields_of_equal_size)
{
  const int size = 2;
  TBitField bf1(size), bf2(size);
  for (int i = 0; i < size; i++)
  {
    bf1.setBit(i);
  }
  bf2 = bf1;

  EXPECT_EQ(bf1, bf2);
}

TEST(TBitField, or_operator_applied_to_bitfields_of_equal_size)
{
  const int size = 4;
  TBitField bf1(size), bf2(size), expBf(size);
  // bf1 = 0011
  bf1.setBit(2);
  bf1.setBit(3);
  // bf2 = 0101
  bf2.setBit(1);
  bf2.setBit(3);

  // expBf = 0111
  expBf.setBit(1);
  expBf.setBit(2);
  expBf.setBit(3);

  EXPECT_EQ(expBf, bf1 | bf2);
}

TEST(TBitField, or_operator_applied_to_bitfields_of_non_equal_size)
{
  const int size1 = 4, size2 = 5;
  TBitField bf1(size1), bf2(size2), expBf(size2);
  // bf1 = 0011
  bf1.setBit(2);
  bf1.setBit(3);
  // bf2 = 01010
  bf2.setBit(1);
  bf2.setBit(3);

  // expBf = 01110
  expBf.setBit(1);
  expBf.setBit(2);
  expBf.setBit(3);

  EXPECT_EQ(expBf, bf1 | bf2);
}

TEST(TBitField, and_operator_applied_to_bitfields_of_equal_size)
{
  const int size = 4;
  TBitField bf1(size), bf2(size), expBf(size);
  // bf1 = 0011
  bf1.setBit(2);
  bf1.setBit(3);
  // bf2 = 0101
  bf2.setBit(1);
  bf2.setBit(3);

  // expBf = 0001
  expBf.setBit(3);

  EXPECT_EQ(expBf, bf1 & bf2);
}

TEST(TBitField, and_operator_applied_to_bitfields_of_non_equal_size)
{
  const int size1 = 4, size2 = 5;
  TBitField bf1(size1), bf2(size2), expBf(size2);
  // bf1 = 0011
  bf1.setBit(2);
  bf1.setBit(3);
  // bf2 = 01010
  bf2.setBit(1);
  bf2.setBit(3);

  // expBf = 00010
  expBf.setBit(3);

  EXPECT_EQ(expBf, bf1 & bf2);
}

TEST(TBitField, can_invert_bitfield)
{
  const int size = 2;
  TBitField bf(size), negBf(size), expNegBf(size);
  // bf = 01
  bf.setBit(1);
  negBf = ~bf;

  // expNegBf = 10
  expNegBf.setBit(0);

  EXPECT_EQ(expNegBf, negBf);
}

TEST(TBitField, can_invert_large_bitfield)
{
  const int size = 38;
  TBitField bf(size), negBf(size), expNegBf(size);
  bf.setBit(35);
  negBf = ~bf;

  for(int i = 0; i < size; i++)
    expNegBf.setBit(i);
  expNegBf.clrBit(35);

  EXPECT_EQ(expNegBf, negBf);
}

TEST(TBitField, invert_plus_and_operator_on_different_size_bitfield)
{
  const int firstSze = 4, secondSize = 8;
  TBitField firstBf(firstSze), negFirstBf(firstSze), secondBf(secondSize), testBf(secondSize);
  // firstBf = 0001
  firstBf.setBit(0);
  negFirstBf = ~firstBf;
  // negFirstBf = 1110

  // secondBf = 00011000
  secondBf.setBit(3);
  secondBf.setBit(4);

  // testBf = 00001000
  testBf.setBit(3);

  EXPECT_EQ(secondBf & negFirstBf, testBf);
}

TEST(TBitField, can_invert_many_random_bits_bitfield)
{
  const int size = 38;
  TBitField bf(size), negBf(size), expNegBf(size);

  std::vector<int> bits;
  bits.push_back(0);
  bits.push_back(1);
  bits.push_back(14);
  bits.push_back(16);
  bits.push_back(33);
  bits.push_back(37);

  for (unsigned int i = 0; i < bits.size(); i++)
    bf.setBit(bits[i]);

  negBf = ~bf;

  for(int i = 0; i < size; i++)
    expNegBf.setBit(i);
  for (unsigned int i = 0; i < bits.size(); i++)
    expNegBf.clrBit(bits[i]);

  EXPECT_EQ(expNegBf, negBf);
}

TEST(TBitField, bitfields_with_different_bits_are_not_equal)
{
  const int size = 4;
  TBitField bf1(size), bf2(size);

  bf1.setBit(1);
  bf1.setBit(3);

  bf2.setBit(1);
  bf2.setBit(2);

  EXPECT_NE(bf1, bf2);
}

//-----------------------------------------------------------------------------
// MY TESTS

TEST(TBitField, MYTEST_can_compare_equally_bitfields)
{
  const int size = 4;
  TBitField bf1(size), bf2(size);

  bf1.setBit(1);
  bf1.setBit(3);

  bf2.setBit(1);
  bf2.setBit(3);

  EXPECT_EQ(bf2 == bf1, 1);
}

TEST(TBitField, MYTEST_can_compare_non_equally_bitfields)
{
  const int size = 4;
  TBitField bf1(size), bf2(size);

  bf1.setBit(1);
  bf1.setBit(2);

  bf2.setBit(1);
  bf2.setBit(3);

  EXPECT_EQ(bf2 == bf1, 0);
}

TEST(TBitField, MYTEST_can_compare_inequaly_bitfields)
{
  const int size = 4;
  TBitField bf1(size), bf2(size);

  bf1.setBit(1);
  bf1.setBit(3);

  bf2.setBit(1);
  bf2.setBit(3);

  EXPECT_EQ(bf2 != bf1, 0);
}

TEST(TBitField, MYTEST_can_compare_non_inequal_bitfields)
{
  const int size = 4;
  TBitField bf1(size), bf2(size);

  bf1.setBit(1);
  bf1.setBit(2);

  bf2.setBit(1);
  bf2.setBit(3);

  EXPECT_EQ(bf2 != bf1, 1);
}

//TEST(TBitField, MYTEST_INPUT)
//{
//  //input 1 0 1
//  //bf = [1 0 1]
//  TBitField bf1(3), bf2(3);
//  bf1.setBit(0);
//  bf1.setBit(2);
//
//  cin >> bf2;
//  EXPECT_EQ(bf1, bf2);
//}
