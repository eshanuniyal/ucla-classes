package hw5;

import java.util.Map;
import java.math.BigInteger;

public class PhoneUtil {
    public static void prependOne(Map<String, BigInteger> m) {
        // adds a 1 to the beginning of all existing phone number entries to indicate that they are US phone numbers

        // iterating over Map m
        for (Map.Entry<String, BigInteger> entry : m.entrySet()) {
            // extracting key and value
            String key = entry.getKey();
            BigInteger value = entry.getValue();
            // computing new value by BigInteger's string input constructor
            BigInteger newValue = new BigInteger('1' + value.toString());
            // updating value in map
            m.replace(key, newValue);
        }
    }
}
