using System;
using TestNinja.Fundamentals;
using NUnit.Framework;
using TestNinja.Fundamentals;

namespace TestNinja.UnitTests
{
    [TestFixture]
    class MathTests
    {
        private Fundamentals.Math _math;
        [SetUp]
        public void SetUp()
        {
            _math = new Fundamentals.Math();
        }

        [Test]
        [Ignore("Nervt!!")]
        public void Add_WhenCalled_ReturnTheSumOfArgument()
        {
            
            var result=_math.Add(1, 2);
            Assert.That(result, Is.EqualTo(3));

        }

        [Test]
        [TestCase(2,1,2)]
        [TestCase(1,2,2)]
        [TestCase(2,2,2)]
        public void Max_WhenCalled_ReturnTheGreaterArgument(int a, int b, int expectedResult)
        {
          
            var result = _math.Max(a,b);
            Assert.That(result, Is.EqualTo(expectedResult));
        }


    }
}
