import BegumNur_interface.*;
import BegumNur_src.*;

/**
 * @Author : Begum Nur
 * @Date : 05.06.2023
 * This class tests the observer-observable pattern of the program.
 */

public class Test {

    public static void main(String[] arg){
        //This is the dataset
        Dataset ds = new Dataset();

        //Creating the observers
        Player p1 = new Player();
        Player p2 = new Player();

        Viewer v1 = new Viewer();
        Viewer v2 = new Viewer();

        //Register the observers to the observable
        ds.register(p1);
        ds.register(p2);
        ds.register(v1);
        ds.register(v2);
        // add elements to the dataset
        ds.add(new Image("imagename1", "dimension info1", "other info1"));
        ds.add(new Image("imagename2", "dimension info2", "other info2"));
        ds.add(new Image("imagename3", "dimension info3", "other info3"));
        ds.add(new Image("imagename4", "dimension info4", "other info4"));
        ds.add(new Image("imagename5", "dimension info5", "other info5"));

        ds.add(new Audio("audioname1", "duration1", "other info1"));
        ds.add(new Audio("audioname2", "duration2", "other info2"));
        ds.add(new Audio("audioname3", "duration3", "other info3"));

        ds.add(new Video("vidoname1", "duration1", "other info1"));
        ds.add(new Video("videoname2", "duration2", "other info2"));
        ds.add(new Video("videoname3", "duration3", "other info3"));

        ds.add(new Text("textname1", "other info1"));
        ds.add(new Text("textname2", "other info2"));
        ds.add(new Text("textname3", "other info3"));

        System.out.println("Getting the currently playing object:");
        //Get the current playing object
        Playable po = p1.currently_playing();
        po.play();

        System.out.println("Removing the currently playing object:");
        ds.remove((DataObject) po);

        System.out.println("Getting the currently playing object again:");
        Playable pl = p1.currently_playing();
        pl.play();

        System.out.println("Getting the currently viewing object:");
        NonPlayable np = v1.currently_viewing();
        np.info();

        System.out.println("Showing the Nonplayable list:");
        v1.show_list();

        System.out.println("Unregistering a viewer observer object from the array.");
        ds.unregister(v1);

        System.out.println("Showing the next NonPlayable text object:");
        try
        {
            v1.next("text");
        }
        catch (IllegalAccessException il){
            System.out.println("Error: " + il.getMessage());
        }




    }



}
