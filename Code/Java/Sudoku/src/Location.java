/**
 * @author Nick Snyder
 * @version 11 November 2021
 */
public class Location {

    private int row;
    private int column;

    /**
     * The constructor for Location.
     * It stores the row and column values.
     *
     * @param r int
     * @param c int
     */
    public Location(int r, int c) {
        row = r;
        column = c;
    }

    /**
     * Returns the Location's row value.
     *
     * @return int
     */
    public int getRow() {
        return row;
    }

    /**
     * Returns the Location's column value.
     *
     * @return int
     */
    public int getColumn() {
        return column;
    }

    /**
     * Gets the next Location after this one.
     *
     * @return Location
     */
    public Location next() {

        Location location = new Location(row, column);

        if (getRow() == 8 && getColumn() == 8) {
            return null;
        }

        if (getColumn() == 8) {
            location.column = 0;
            location.row++;
        } else {
            location.column++;
        }

        return location;
    }

    @Override
    public String toString() {
        return row + ", " + column;
    }
}
