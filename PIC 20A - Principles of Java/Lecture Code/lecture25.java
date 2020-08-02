// Lecture 25 | Friday, Week 9

// ---------------------------------------------------------------------------------------------------------
// Streams and I/O
// Often, you want to do I/O without paying attention to where you are reading from or writing to
// You can read from or write to a file, the console, a network connection, or a peripheral device
// You must establish such I/O channels in their own specific ways
// Once a connection is established you have a "stream", and you can polymorphically read from or write to a stream

// introductory example
String s = "http://www.math.ucla.edu/~eryu//courses/pic20a/lectures/RJ.txt";
URL url = new URL(s);
InputStream in = url.openStream();
OutputStream out = System.out;
while (true) {
	int nextByte = in.read();
	if (nextByte == -1)
		break;
	out.write((char) nextByte);
}
in.close();
out.close();
// the read and write code doesn't know what kind of streams it is using

// abstract class InputStream
	// an InputStream reads (from somewhere) one byte at a time
	public abstract int read() throws IOException {}
		// reads and return a byte of data; it returns -1 if end of stream is reached
	public void close() throws IOException {}
		// closes the stream and releases any system resources associated with the stream

// InputStream hierarchy (all classes are in the package java.io)
/*		InputStream
	   /		   \	
FileInputStream		FilterInputStream
						|
					BufferInputStream

*/

// abstract class OutputStream
	// an OutputStream writes (to somewhere) one byte at a time
	public abstract void write(int b) throws IOException {}
		// writes a byte of data
	public void close() throws IOException {}
		// closes the stream and releases any system resources associated with the stream

// OutputStream hierarchy (all classes are in the package java.io)
/*		OutputStream
	   /		   \	
FileOutputStream	FilterOutputStream
						|			   \
					BufferOutputStream	PrintStream
*/

// FileInputStream and FileOutputStream
// FileInputStream reads bytes from a file and FileOutputStream writes bytes to a file
InputStream in;
OutputStream out;
in = new FileInputStream("filename1");
out = new FileOutputStream("filename2");
while (true) {
	int nextByte = in.read();
	if (nextByte == -1)
		break;
	out.write((char) nextByte);
}
in.close();
out.close();


// in addition to the methods inherited, PrintStream has additional methods such as
public void println(int x) {}
public void println(double x) {}
public void println(Object x) {}
...;
// PrintStream never throws an IOException; rather, you can use
public boolean checkError() {}

// System I/O
// Most operating systems (Windows, macOS, and Linux) have 3 standard streams: standard input, standard output, and standard error
	// you can interact with them through the command line
	// Use the fields of class System
		public static InputStream in;
		public static PrintStream out;
		public static PrintStream err;
		// to access these standard streams

// modified example
InputStream in;
OutputStream out;
in = System.in;
out = System.out;
while (true) {
	int nextByte = in.read();
	if (nextByte == -1)
		break;
	out.write((char) nextByte);
}
in.close();
out.close();

// Always close streams
// Streams often handle scarce, finite resources; you can run out of them if you don't clean up properly
// always close them and close them within a finally block
// when you don't close streams, they are usually closed when your program terminates
	// for small programs, this is usually okay
// however, there's a reason experienced programmers insist that you close streams and that you do so with a finally block
	// this is because streams can throw IOExceptions
	// since the methods of InputStream and OutputStream use checked exceptions ("throws IOException"), we need to check for them in our code

// modified example
InputStream in;
OutputStream out;
in = System.in;
out = System.out;
while (true) {
	int nextByte = in.read();
	if (nextByte == -1)
		break;
	out.write((char) nextByte);
}
// closing streams
if (in != null) {
	// we check for the stream being null can only try to close a stream if we managed to open it
	try {
		in.close();
	// it is required we catch an IOException
	} catch (IOException ex) {
		System.out.println("Stream close failed");
	}
}
if (out != null) {
	try {
		out.close();
	} catch (IOException ex) {
		System.out.println("Stream close failed");
	}
}

// when you duck the exception handling, you can use try-finally to ensure the streams are closed
public void fn() throws Exception {
	InputStream in = null;
	try {
		in = new FileInputStream("filename.txt");
		// do stuff with in
		...
	} finally {
		in.close();
	}
}
// the try-finally construct does not catch any exceptions, but is nevertheless useful

// Buffered streams
	// the streams we've talked about perform unbuffered I/O
		// this means the bytes are read or written one byte at a time
		// this can be inefficient if there is a fixed cost associated with each read/write
	// buffered input streams read in bulk, and store the data in a buffer
		// reading each byte retrieves the bytes from the buffer
	// buffered output stream stores the individual writes into a buffer
		// when the buffer is full, the entire buffer is written in bulk

// in Java, BufferedInputStream is an InputStream, and it's created (via the constructor) with an InputStream
// the same is true with BufferedOutputStream and OutputStream
// BufferedInputStream and BufferedOutputStream are wrappers
	// a wrapper is something that uses another functionality and provides improved efficiency or convenience

// in this example, buffered streams provide a huge speed-up
InputStream in = null;
OutputStream out = null;
try {
	in = new FileInputStream("filaname1");
	in = new BufferedInputStream(in);
	out = new FileOutputStream("filaname2");
	out = new BufferedOutputStream(out);
	while (true) {
		int nextByte = in.read();
		if (nextByte == -1)
			break;
		out.write((char) nextByte);
	}
} finally {
	in.close(); out.close();
}

// avoid using byte streams
	// all streams are implicitly or explicitly built with byte streams, so it's important to understand them
	// however, you should only use byte streams when you actually want to input/output bytes
	// if you want to input/output characters, use a charater stream; it's more convenient and less error-prone
	// to input/output primitive types and Objects, use data streams and object streams respectively

// Readers and Writers
// in Java, character streams are java.io.Readers and java.io.Writers

// Readers and Writers are built upon InputStreams and OutputStreams
InputStream is = new FileInputStream("name1");
OutputStream os = new FileOutputStream("name2");
Reader r = new InputStreamReader(is);
Writer w = new OutputStreamWriter(os);
// same as
Reader r = new FileReader("name1");
Writer w = new FileWriter("name2");

// for efficiency sake, you want to use BufferedReaders and BufferedWriters
Reader r;
Writer w;
...
BufferedReader br = new BufferedReader(r);
BufferedWriter bw = new BufferedWriter(w);

// with BufferedReader, you can read an entire line
String line = br.readLine();

// Character encoding and internationalisation
	// The simplest way to encode English characters is via ASCII, which uses 8 bits per character
	// Java, however, supports 16-bit unicode characters (which is fortunately backwards-compatible with ASCII)
	// To represent characters from languages like Arabic, Chinese, Greek, Hebrew, Hindi, Japanese, Korean, or Russian, you need to use unicode
	// Internationalisation is adapting a program to different languages, regional differences and technical requirements of a target locale
	// Just remember that Java's character streams have great support for internationalisation

// Scanning and formatting
// I/O often involves translating between computer-readable and human-readable representations of data
// "Scanner" translates human-readable strings into computer-readable data
// "format" translates computer-readable data into human-readable strings

// java.util.Scanner can produce ints, doubles, et cetera from a String or an InputStream
Scanner s;
s = new Scanner("FFF");
int i = s.nextInt(16);	// read as base 16
s = new Scanner(System.in);
double d = s.nextDouble();	// read from command line

// PrintStream and PrintWriter have the method "format"
int i = 2;
double r = Math.sqrt(i);
PrintStream o = System.out;
o.println("sqrt of " + i " is " + r + ".");
o.format("sqrt of %d is %.2f.%n", i, r);
	// %d is a placeholder for an interger
	// %f is a placeholder for a floating point number; .2 indicates to print two digits after the decimal
	// %n is just the newline character