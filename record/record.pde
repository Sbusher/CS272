/* Processing.org code to plot data sent from the Arduino.  Have the Arduino send out data on the serial port as
numbers separated by tabs, one line for each set of data:

number \t number \t number \n

with up to 6 numbers.  This code will map that data to whatever range you want and then plot
as a live data scrolling past in one window.  Example Arduino code is in comments at the bottom.

I haven't cleaned this up yet, so think of it as an example.

-Scot

*/

import processing.serial.*;

int baudRate = 9600;//57600;//28800;
int serialPortIndex = 0;        // 0 on my mac, 1 on Jeff's PC (COM10)
String usage = "Keyboard: 1 to start or resume acquisition, 0 to pause, s to start recording, x to stop recording, q to quit"; 

// Serial port object
Serial sp;
// where we'll temporarily store each data point (up to 6 channels of data)
int[] data = new int[6];        // just making this bigger than expected
// colors for plotting
int[][] dataColor = {{0,0,255},{0,255,0},{255,0,0},{255,255,0},{255,0,255},{0,255,255}};
int numberOfDataPoints = 0;
int pos = 0;        // horizontal position of "cursor" for plotting

// keep track of whether or not we are recording
boolean recording = false;

// For writing data to file
PrintWriter writer;
String filename;
File file;
String filenameBase = "data_";        // file will be "data_001.txt", "data_002.txt", etc.
int filenameStartingIndex = 1;

long startTime = System.nanoTime();

PFont font;
boolean firstTime = true;

void setup()
{
    // make the plotting window 1024 x 1024, this is then the range for the data
    // to plot it in this window just make sure it is in this range.  Works perfectly for
    // 10 bit data from the Arduino
    size(1024,512,P2D);
    // list all serial ports to see which one we might need to go to (serialPortIndex variable above)
    println(Serial.list());
    sp = new Serial( this, Serial.list()[serialPortIndex], baudRate );
    // Writing a 0 to the Arduino.  To use this the Arduino code needs to listen for this character 
    // and then start sending data.  This is to have the Arduino send data or not.  Don't need this for testing
    //sp.write('0');    // make sure the Arduino is stopped when we start
    sp.bufferUntil('\n');
    background(255);
    //font = loadFont("Geneva-18.vlw");
    //textFont(font);
}

void draw()
{
    if( recording )
    {
        background( 255 );
        fill(255,0,0);
        text("Recording to file: " + filename, 400, 500);
        return;
    }
    if( pos == 0 || pos >= 1023 )
    {
        background( 255 );
        pos = 0;
        fill(0,0,0);
        text(usage, 15, 17);
    }
    // for each data point sent, you can map it differently
    for( int i = 0; i < numberOfDataPoints; i++ )
    {
        stroke(dataColor[i][0],dataColor[i][1],dataColor[i][2]);
        double value = 0.0;
        if( i == 0 )
        {
             // temperature, 201 = 20.1 C  
             // !!***** Adjust map for whatever data you're getting from the Arduino ****!!
            //value = map(data[i]/10.0,-20,40,512,1028);
           value = data[i] / 2; 
        }
        else if( i == 1 )
        {
            // pressure: 101325 = 101.325 kPa
            value = map(data[i]/1000.0,98,102,0,512);
        }
        int y = 512 - (int)value;
        //int y = 1028-data[i];    // 0 is at the top
        rect(pos,y,2,2);
        //point(pos,y);        
    }
}

/* Invoked by the system when we have serial data to read (was buffered until a newline).  
  Grab the serial data as a string and parse out our values
  */
void serialEvent( Serial p )
{
    // First line may be incomplete
    if(firstTime)
    {
        firstTime = false;
        return;
    }
    String s = p.readString();
    String[] sbuf = s.split("\t");            // Tab delimited data from the Arduino
    System.out.println(sbuf[0]);
    numberOfDataPoints = sbuf.length;
    try
    {
        for( int i = 0; i < sbuf.length; i++ )
        {
            data[i] = Integer.parseInt(sbuf[i].trim());
        }
        pos++;
        if( recording )
        {
            //writer.print( System.currentTimeMillis()  "\t");
            writer.print( (System.nanoTime() - startTime) + "\t");
            for( int i = 0; i < sbuf.length; i++ )
            {
                writer.print(data[i] + "\t");
            }
            writer.println();
        }
    }
    catch(NumberFormatException e )
    {
           // didn't catch all the characters for this data point, ignore it
           numberOfDataPoints = 0;    // so we don't plot it
    }
    
}

/* Get user interaction through the keyboard.  This was just the quickest way to do this
  in Processing.  If you use full Java it would be more convenient to use buttons
  and textfields, ...
  */
void keyTyped()
{
    if( key == '0' )
    {
        sp.write('0');        // 0 means stop acquisition. Arduino listens for this
    }
    else if( key == '1' )      // 1 means start or resume acquisition
    {
        sp.write('1');
    }
    else if( key == 's' )            // begin recording to file
    {
        startRecording();
    }
    else if( key == 'x' )            // stop recording to file
    {
        stopRecording();
    }
    else if( key == 'q' )            // quit
    {
        // quit nicely
        sp.write('0');
        recording = false;
        if( writer != null )
        {
            writer.flush();
            writer.close();
        }
        exit();
    }
}

void startRecording()
{
  if( recording )
    {
        println("We're already recording");
    }
    else
    {
        recording = true;
    // try to slow down painting
    frameRate(10);
        sp.write('1');
        // open a file and get going
        getNewFilename();
        try
        {
            writer = new PrintWriter(new BufferedWriter(new FileWriter(file)));
        }
        catch(IOException e)
        {
            recording = false;
            println("There was an error opening the file to write to");
            sp.write('0');
        }
    }
}

void stopRecording()
{
  if( recording )
    {
        recording = false;
        if( writer != null )
        {
            writer.flush();
            writer.close();
        }
        sp.write('0');
    // speed it back up
    frameRate(30);
    }
    else
    {
        println("We weren't recording anyway");
    }
}

/* Get a valid filename.  Keep trying until we get one that doesn't exist, i.e. in the format of
  data_001.txt, data_002.txt, ... 
  
  Places filename in: File file and String filename above*/
void getNewFilename()
{
    int index = filenameStartingIndex;
    String name;
    while( true )
    {
        if( index < 10 )
            name = filenameBase+  "00" + index  +".txt";
        else if( index < 100 )
            name = filenameBase+  "0" + index+  ".txt";
        else
            name = filenameBase+  index+  ".txt";
        println("Trying filename: " + name);
        file = new File(name);
        if( !file.exists() )
            break;    // this one's ok
        index++;
    }
  filename = name;
    // valid name is now in file and filename
}


/*
    Example Arduino code for two variables

int x = 0;
int y = 1023;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  
  if( x == 1023)
      x = 0;
  if( y == 0 )
      y = 1024;
  x;
  y--;
  Serial.print(x);
  Serial.print('\t');
  Serial.print(y);
  Serial.println();
  
  delay(10);
}

*/

