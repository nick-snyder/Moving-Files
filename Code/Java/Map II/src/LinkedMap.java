import java.util.Scanner;

/**
 * @author Nicholas Snyder
 * @version 2 November 2021
 *
 * @param <K> key
 * @param <V> value
 */
public class LinkedMap<K, V> implements Map<K, V> {

    public LinkedList<Entry<K, V>> list;
    public K key;
    public V value;

    /**
     *
     * @param <K> key
     * @param <V> value
     */
    public class Entry<K, V> implements Map.Entry<K, V> {

        private K key;
        private V value;

        /**
         * Entry.
         *
         * @param key K
         * @param value V
         */
        public Entry(K key, V value) {
            this.key = key;
            this.value = value;
        }

        /**
         * Returns the key corresponding to this entry.
         *
         * @return the key corresponding to this entry
         */
        @Override
        public K getKey() {
            return key;
        }

        /**
         * Returns the value corresponding to this entry.
         *
         * @return the value corresponding to this entry
         */
        @Override
        public V getValue() {
            return value;
        }

        /**
         * Returns a string representation of this Entry.
         *
         * @return String
         */
        @Override
        public String toString() {
            return String.format("(%s, %s)", key, value);
        }

        /**
         * Compares an object o to this entry.
         *
         * @param o Object
         * @return boolean
         */
        @SuppressWarnings("unchecked")
        public boolean equals(Object o) {

            if (o == this) {
                return true;
            }


            if (o instanceof Entry) {

                Entry<K, V> e = (Entry<K, V>) o;
                return e.getKey().equals(key) && e.getValue().equals(value);

            } else {
                return key.equals(o);
            }
        }
    }

    /**
     * Linked map.
     */
    public LinkedMap() {
        this.list = new LinkedList<>();
    }

    /**
     * gets lists.
     *
     * @return LinkedList
     */
    public LinkedList<Entry<K, V>> getList() {
        return list;
    }

    /**
     * Associates the specified value with the specified key in this map.
     * If the map previously contained a mapping for the key,
     * the old value is replaced by the specified value.
     *
     * @param key   key with which the specified value is to be associated
     * @param value value to be associated with the specified key
     * @return the previous value associated with key, or null if there was
     * no mapping for key.
     * (A null return can also indicate that the map previously associated
     * null with key, if the implementation supports null values.)
     */
    @Override
    public V put(K key, V value) {  // add

        V v = get(key);

        if (!containsKey(key)) {
            Entry<K, V> entry = new Entry<K, V>(key, value);
            list.add(entry);
        } else {
            Entry<K, V> entry = list.get(key);
            entry.value = value;
        }
        return v;
    }

    /**
     * If the specified key is not already associated with a value
     * (or is mapped to null) associates it with the given value and
     * returns null, else returns the current value.
     *
     * @param key   key with which the specified value is to be associated
     * @param value value to be associated with the specified key
     * @return the previous value associated with key, or null if there
     * was no mapping for key.
     * (A null return can also indicate that the map previously associated
     * null with key,
     * if the implementation supports null values.)
     */
    @Override
    public V putIfAbsent(K key, V value) {  // add
        V v = get(key);

        if (!containsKey(key)) {
            Entry<K, V> entry = new Entry<K, V>(key, value);
            list.add(entry);
        }
        return v;
    }

    @Override
    public String toString() {

        return list.toString();
    }

    /**
     * Removes all of the mappings from this map.
     * The map will be empty after this call returns.
     */
    @Override
    public void clear() {
        list.clear();
    }

    /**
     * Returns the value to which the specified key is mapped,
     * or null if this map contains no mapping for the key.
     * If this map permits null values, then a return value of null does not necessarily indicate
     * that the map contains no mapping for the key;
     * it's also possible that the map explicitly maps the key to null.
     * The Map#containsKey operation may be used to distinguish these two cases.
     *
     * @param key the key whose associated value is to be returned
     * @return the value to which the specified key is mapped,
     * or null if this map contains no mapping for the key
     */
    @Override
    public V get(K key) {


        if (list.get(key) != null) {
            return list.get(key).value;
        } else {
            return null;
        }
    }

    /**
     * Returns true if this map contains a mapping for the specified key.
     *
     * @param key key whose presence in this map is to be tested
     * @return true if this map contains a mapping for the specified key
     */
    @Override
    public boolean containsKey(K key) {
        Entry<K, V> entry = list.get(key);
        return entry != null;
    }

    /**
     * Returns true if this map contains no key-value mappings.
     *
     * @return true if this map contains no key-value mappings
     */
    @Override
    public boolean isEmpty() {
        return list.size() == 0;
    }

    /**
     * Removes the mapping for a key from this map if it is present.
     * Returns the value to which this map previously associated the key,
     * or null if the map contained no mapping for the key.
     * If this map permits null values, then a return value of null does not necessarily indicate
     * that the map contained no mapping for the key;
     * it's also possible that the map explicitly mapped the key to null.
     * The map will not contain a mapping for the specified key once the call returns.
     *
     * @param key key whose mapping is to be removed from the map
     * @return the previous value associated with key, or null if there was no mapping for key.
     */
    @Override
    public V remove(K key) {

        V v = get(key);

        for (int i = 0; i < list.size(); i++) {
            if (list.get(i).key.equals(key)) {
                list.remove(list.get(i));
            }
        }
        return v;
    }

    /**
     * Returns the number of key-value mappings in this map.
     *
     * @return the number of key-value mappings in this map
     */
    @Override
    public int size() {
        return list.size();
    }

    /**
     * main.
     *
     * @param args String[]
     */
    public static void main(String[] args) {
        LinkedMap<String, Integer> linkedMap = new LinkedMap<>();
        Scanner scanner = new Scanner(System.in);
        String command;

        String key;
        int value;

        while (true) {
            String input = scanner.nextLine();
            String[] inputs = input.split(" ");
            command = inputs[0];
            if (command.equals("x")) {
                break;
            } else {
                switch (command) {
                    case "p":
                        key = inputs[1];
                        value = Integer.parseInt(inputs[2]);
                        linkedMap.put(key, value);
                        System.out.println(linkedMap.getList());
                        break;
                    case "P":
                        key = inputs[1];
                        value = Integer.parseInt(inputs[2]);
                        linkedMap.putIfAbsent(key, value);
                        System.out.println(linkedMap.getList());
                        break;
                    case "c":
                        key = inputs[1];
                        //linkedMap.containsKey(key);
                        System.out.println(linkedMap.containsKey(key));
                        break;
                    case "C":
                        linkedMap.clear();
                        System.out.println(linkedMap.getList());
                        break;
                    case "g":
                        key = inputs[1];
                        System.out.println(linkedMap.get(key));
                        break;
                    case "s":
                        linkedMap.size();
                        System.out.println(linkedMap.size());
                        break;
                    case "e":
                        System.out.println(linkedMap.isEmpty());
                        break;
                    case "r":
                        key = inputs[1];
                        linkedMap.remove(key);
                        System.out.println(linkedMap.getList());
                        break;
                }
            }
            System.out.println("------------------");
        }
        scanner.close();
    }
}
