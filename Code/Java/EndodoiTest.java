// import org.junit.Test;
// import static org.junit.Assert.*;
// public class EndodoiTest {
//     @Test
//     public void drawBoard1(){
//         String expected = " +====++==++----+----+\n"
//                         + "1|(  )||  ||(  )|(  )|\n"
//                         + " | st ||  ||  a |  b |\n"
//                         + " +====++==++----+----+\n"
//                         + "2|(  )||  ||(  )|(  )|\n"
//                         + " | st ||  ||  c |  d |\n"
//                         + " +====++==++----+----+\n";
//         int [][] pits = {{0,0},{0,0}};
//         String actual = Endodoi.drawBoard(pits, 0, 0, '!', -1);
//         assertEquals(expected,actual);
//     }
//     @Test
//     public void drawBoard0(){
//         String expected = " +====++==++----+----+----+----+----+----+----+----+----+----+----+----+\n"
//                         + " 1|(  )||  ||( 6)|( 3)|( 2)|( 6)|( 3)|( 4)|( 3)|( 5)|( 5)|( 2)|( 1)|( 2)|\n"
//                         + " | st ||  ||    |    |    |    |    |    |    |    |    |    |    |    |\n"
//                         + " +====++==++----+----+----+----+----+----+----+----+----+----+----+----+\n"
//                         + "2|( 2)||\\/||( 1)|( 4)|( 2)|( 6)|( 4)|( 5)|(  )|(  )|( 6)|( 1)|( 1)|( 4)|\n"
//                         + " | st ||/\\||  m |  n |  o |  p |  q |  r |  s |  t |  u |  v |  w |  * |\n"
//                         + " +====++==++----+----+----+----+----+----+----+----+----+----+----+----+\n";
//         int [][] pits = {{6,3,2,6,3,4,3,5,5,2,1,2},{1,4,2,6,4,5,0,0,6,1,1,4}};
//         String actual = Endodoi.drawBoard(pits, 0, 2, 'x', 2);
//         if(!expected.equals(actual)) {
//             System.out.println("Incorrect result. Expected:");
//             System.out.println(expected);
//             System.out.println("Actual:");
//             System.out.println(actual);
//         }
//         assertEquals(expected, actual);
//     }
//     @Test
//     public void pit2Coordinates1() {
//         int [] expectedCoordinates = new int[] {0, 1};
//         int [] actualCoordinates =  Endodoi.pit2Coordinates('b', new int[][]{{0,0},{0,0} });
//         assertArrayEquals(expectedCoordinates, actualCoordinates);
//     }
//     @Test
//     public void myPit2Coordinates() {
//         int[] expectedCoordinates = new int[]{0, 7};
//         int[] actualCoordinates = Endodoi.pit2Coordinates('h', new int[][]{{6,3,2,6,3,4,3,5,5,2,1,2},{1,4,2,6,4,5,0,0,6,1,1,4}});
//         assertArrayEquals(expectedCoordinates, actualCoordinates);
//     }
//     @Test
//     public void getOpposingPit() {
//         char expected = 'd';
//         char actual = Endodoi.getOpposingPit('b', new int[][]{{0, 0}, {0, 0}});
//         assertEquals(expected, actual);
//     }
//     @Test
//     public void myGetOpposingPit() {
//         char expected = 't';
//         char actual = Endodoi.getOpposingPit('h', new int[][]{{6,3,2,6,3,4,3,5,5,2,1,2},{1,4,2,6,4,5,0,0,6,1,1,4}});
//         assertEquals(expected, actual);
//     }
// }