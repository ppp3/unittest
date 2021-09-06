using System;
using TestNinja.Fundamentals;
using NUnit.Framework;

namespace TestNinja.UnitTests
{
    [TestFixture]
    public class ReservationTests
    {
        [Test]
        public void CanBeCancelledBy_AdminCacnelling_ReturnsTrue()
        {
            var reservation = new Reservation();

            var result=reservation.CanBeCancelledBy(new User { IsAdmin = true });
            
            Assert.IsTrue(result);
        }

        [Test]
        public void CanBeCancelledBy_SameUserCancelling_ReturnsTrue()
        {
            var reservation = new Reservation();
            var user = new User { IsAdmin = false };
            
            reservation.MadeBy = user;
            var result = reservation.CanBeCancelledBy(user);
            
            Assert.IsTrue(result);
        }

        [Test]
        public void CanBeCancelledBy_AnotherUserCanecelling_ReturnsFalse()
        {
            var reservation = new Reservation { MadeBy = new User() };
            
            var result = reservation.CanBeCancelledBy(new User());

            Assert.IsFalse(result);
        }

    }
}
