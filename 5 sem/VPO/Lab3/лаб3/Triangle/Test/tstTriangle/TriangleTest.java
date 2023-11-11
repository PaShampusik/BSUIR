package tstTriangle;

import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import junit.framework.Assert;
import triangle.Triangle;

public class TriangleTest {

	private double parameterA, parameterB, parameterC;

	@Before
	public void setUp() throws Exception {

	}

	@After
	public void tearDown() throws Exception {
	}

	@Test
	public void checkTriangle_Correct_tst() {
		parameterA = 15;
		parameterB = 12;
		parameterC = 14;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertTrue(triangle.checkTriangle());

	}

	@Test
	public void checkTriangle_Zero_A_tst() {
		parameterA = 0;
		parameterB = 12;
		parameterC = 14;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertFalse(triangle.checkTriangle());
	}

	@Test
	public void checkTriangle_Zero_B_tst() {
		parameterA = 15;
		parameterB = 0;
		parameterC = 14;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertFalse(triangle.checkTriangle());
	}

	@Test
	public void checkTriangle_Zero_C_tst() {
		parameterA = 15;
		parameterB = 12;
		parameterC = 0;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertFalse(triangle.checkTriangle());
	}

	@Test
	public void checkTriangle_Negative_A_tst() {
		parameterA = -15;
		parameterB = 12;
		parameterC = 14;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertFalse(triangle.checkTriangle());
	}

	@Test
	public void checkTriangle_Negative_B_tst() {
		parameterA = 15;
		parameterB = -12;
		parameterC = 14;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertFalse(triangle.checkTriangle());
	}

	@Test
	public void checkTriangle_Negative_C_tst() {
		parameterA = 15;
		parameterB = 12;
		parameterC = -14;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertFalse(triangle.checkTriangle());
	}

	@Test
	public void checkTriangle_Three_More_C_tst() {
		parameterA = 15;
		parameterB = 12;
		parameterC = 14;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertTrue(triangle.checkTriangle());
	}

	@Test
	public void checkTriangle_Three_More_B_tst() {
		parameterA = 15;
		parameterB = 12;
		parameterC = 14;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertTrue(triangle.checkTriangle());
	}

	@Test
	public void checkTriangle_Three_More_A_tst() {
		parameterA = 15;
		parameterB = 12;
		parameterC = 14;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertTrue(triangle.checkTriangle());
	}

	@Test
	public void checkTriangle_Three_Less_C_tst() {
		parameterA = 1;
		parameterB = 2;
		parameterC = 14;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertFalse(triangle.checkTriangle());
	}

	@Test
	public void checkTriangle_Three_Less_B_tst() {
		parameterA = 5;
		parameterB = 12;
		parameterC = 1;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertFalse(triangle.checkTriangle());
	}

	@Test
	public void checkTriangle_Three_Less_A_tst() {
		parameterA = 15;
		parameterB = 1;
		parameterC = 1;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertFalse(triangle.checkTriangle());
	}

	@Test
	public void checkTriangle_Three_Equal_C_tst() {
		parameterA = 5;
		parameterB = 5;
		parameterC = 10;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertFalse(triangle.checkTriangle());
	}

	@Test
	public void checkTriangle_Three_Equal_B_tst() {
		parameterA = 5;
		parameterB = 10;
		parameterC = 5;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertFalse(triangle.checkTriangle());
	}

	@Test
	public void checkTriangle_Three_Equal_A_tst() {
		parameterA = 10;
		parameterB = 5;
		parameterC = 5;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertFalse(triangle.checkTriangle());
	}

	@Test
	public void detectTriangle_Restangular_1_tst() {
		parameterA = 3;
		parameterB = 4;
		parameterC = 5;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertEquals(triangle.detectTriangle(), 8);
	}

	@Test
	public void detectTriangle_Restangular_2_tst() {
		parameterA = 5;
		parameterB = 4;
		parameterC = 3;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertEquals(triangle.detectTriangle(), 8);
	}

	@Test
	public void detectTriangle_Restangular_3_tst() {
		parameterA = 2;
		parameterB = 5;
		parameterC = 4;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertEquals(triangle.detectTriangle(), 8);
	}

	@Test
	public void detectTriangle_Equilateral_tst() {
		parameterA = 2;
		parameterB = 2;
		parameterC = 2;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertEquals(triangle.detectTriangle(), 0);
	}

	@Test
	public void detectTriangle_Isosceles_1_tst() {
		parameterA = 2;
		parameterB = 2;
		parameterC = 3;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertEquals(triangle.detectTriangle(), 2);

	}

	@Test
	public void detectTriangle_Isosceles_2_tst() {
		parameterA = 3;
		parameterB = 2;
		parameterC = 2;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertEquals(triangle.detectTriangle(), 2);

	}

	@Test
	public void detectTriangle_Isosceles_3_tst() {
		parameterA = 2;
		parameterB = 3;
		parameterC = 2;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertEquals(triangle.detectTriangle(), 2);

	}

	@Test
	public void detectTriangle_Isosceles_Restangular_tst() {
		parameterA = 2;
		parameterB = 2;
		parameterC = 2 * Math.sqrt(2);
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertEquals(triangle.detectTriangle(), 0);

	}

	@Test
	public void detectTriangle_Ordinary_tst() {
		parameterA = 1;
		parameterB = 3;
		parameterC = 8 * Math.sqrt(2);
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertEquals(triangle.detectTriangle(), 4);

	}

	// OWN TESTS
	@Test
	public void detectTriangle_Isosceles_own_1_tst() {
		parameterA = 5;
		parameterB = 5;
		parameterC = 3;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertEquals(triangle.detectTriangle(), 2);
	}

	@Test
	public void detectTriangle_Isosceles_own_2_tst() {
		parameterA = 6;
		parameterB = 8;
		parameterC = 8;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertEquals(triangle.detectTriangle(), 2);
	}

	@Test
	public void detectTriangle_Isosceles_own_3_tst() {
		parameterA = 12;
		parameterB = 9;
		parameterC = 12;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertEquals(triangle.detectTriangle(), 2);
	}

	@Test
	public void detectTriangle_Isosceles_own_4_tst() {
		parameterA = 10;
		parameterB = 8;
		parameterC = 7;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertEquals(triangle.detectTriangle(), 2);
	}

	@Test
	public void detectTriangle_Restangular_own_1_tst() {
		parameterA = 5;
		parameterB = 4;
		parameterC = 3;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertEquals(triangle.detectTriangle(), 8);
	}

	@Test
	public void detectTriangle_Restangular_own_2_tst() {
		parameterA = 5;
		parameterB = 12;
		parameterC = 13;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertEquals(triangle.detectTriangle(), 8);
	}

	@Test
	public void detectTriangle_Restangular_own_3_tst() {
		parameterA = 7;
		parameterB = 24;
		parameterC = 25;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertEquals(triangle.detectTriangle(), 8);
	}

	@Test
	public void detectTriangle_Restangular_own_4_tst() {
		parameterA = 25;
		parameterB = 26;
		parameterC = 7;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertEquals(triangle.detectTriangle(), 8);
	}

	@Test
	public void detectTriangle_Ordinary_own_1_tst() {
		parameterA = 5;
		parameterB = 6;
		parameterC = 7;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertEquals(triangle.detectTriangle(), 4);
	}

	@Test
	public void detectTriangle_Ordinary_own_2_tst() {
		parameterA = 9;
		parameterB = 12;
		parameterC = 10;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertEquals(triangle.detectTriangle(), 4);
	}

	@Test
	public void detectTriangle_Ordinary_own_3_tst() {
		parameterA = 8;
		parameterB = 11;
		parameterC = 10;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertEquals(triangle.detectTriangle(), 4);
	}

	@Test
	public void detectTriangle_Ordinary_own_4_tst() {
		parameterA = 3;
		parameterB = 6;
		parameterC = 4;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertEquals(triangle.detectTriangle(), 2);
	}

	@Test
	public void get_square_own_1_tst() {
		parameterA = 5;
		parameterB = 4;
		parameterC = 3;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertEquals(triangle.getSquare(), 6.0, 0.2);
	}

	@Test
	public void get_square_own_2_tst() {
		parameterA = 6;
		parameterB = 8;
		parameterC = 10;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertEquals(triangle.getSquare(), 24.0, 0.2);
	}

	@Test
	public void get_square_own_3_tst() {
		parameterA = 25;
		parameterB = 24;
		parameterC = 7;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertEquals(triangle.getSquare(), 84.0, 0.2);
	}

	@Test
	public void get_square_own_4_tst() {
		parameterA = 5;
		parameterB = 7;
		parameterC = 6;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertEquals(triangle.getSquare(), 14.7, 0.2);
	}

	@Test
	public void get_square_own_5_tst() {
		parameterA = 12;
		parameterB = 10;
		parameterC = 9;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertEquals(triangle.getSquare(), 44.03, 0.2);
	}

	@Test
	public void get_square_own_6_tst() {
		parameterA = 10;
		parameterB = 10;
		parameterC = 7;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertEquals(triangle.getSquare(), 32.76, 0.2);
	}

	@Test
	public void get_square_own_7_tst() {
		parameterA = 9;
		parameterB = 12;
		parameterC = 12;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertEquals(triangle.getSquare(), 50.05, 0.2);
	}

	@Test
	public void get_square_own_8_tst() {
		parameterA = 0;
		parameterB = 6;
		parameterC = 8;
		Triangle triangle = new Triangle(parameterA, parameterB, parameterC);
		assertEquals(triangle.getSquare(), 15.87, 0.2);
	}
}
