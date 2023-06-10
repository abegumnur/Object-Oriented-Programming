package BegumNur_src;

import BegumNur_interface.IObserver;
import BegumNur_interface.Playable;

import java.util.ArrayList;
import java.lang.IllegalAccessException;
/**
 * @Author : Begum Nur
 * @Date : 05.06.2023
 * Represent a type of observable in the observer pattern.
 * Player observers are interested in the changes that has been made to the Playable objects only.
 */
public class Player implements IObserver {

    private ArrayList<Playable> playlist;
    /**
     * Represents the index of the currently playing object.
     */
    private int current_index;

    public Player(){
        playlist = new ArrayList<>();
        current_index = 0;
    }

    public Playable currently_playing(){
        return playlist.get(current_index);
    }

    /**
     * Skip to the next Playable object.
     * @param type If audio, skip to the closest next Audio  object, if video skip to the closest next Video object.
     * @exception IllegalAccessException if the playlist is empty.
     */
    public void next(String type) throws IllegalAccessException {
        if(playlist.size() == 0){
            throw new IllegalAccessException("Empty playlist. Cannnot play the next item.\n");
            //System.out.println("Empty playlist. Cannot play the next item...");
        }

        if(type.equals("audio")){
            for(int i = current_index + 1; i < playlist.size(); i++){
                if(playlist.get(i) instanceof Audio){
                    // update the current index appropriately
                    current_index = i;
                    // play the audio object
                    playlist.get(current_index).play();
                    break;
                }
            }
        }

        else if(type.equals("video")){
            for(int i = current_index + 1; i < playlist.size(); i++){
                if(playlist.get(i) instanceof Video){
                    // update the current index appropriately
                    current_index = i;
                    // play the video object
                    playlist.get(current_index).play();
                    break;
                }

            }
        }


    }

    /**
     * Skip to the previous Playable object.
     * @param type if audio plays the previous audio object, if video plays the previous object
     * @throws IllegalAccessException if the playlist is empty.
     */

    public void previous(String type) throws IllegalAccessException {
        if(playlist.size() == 0){
            throw new IllegalAccessException("Empty playlist. Cannot play the previous item...\ns");
            //System.out.println("Empty playlist. Cannot play the previous item...");
        }

        if(type.equals("audio")){
            for(int i = current_index - 1; i >= 0; i--) {
                if (playlist.get(i) instanceof Audio) {
                    current_index = i;
                    playlist.get(current_index).play();
                    break;
                }
            }
        }

        else if(type.equals("video")) {
            for (int i = current_index - 1; i >= 0; i--){
                if (playlist.get(i) instanceof Video) {
                    current_index = i;
                    playlist.get(current_index).play();
                    break;
                }
            }
        }
    }


    public void show_list(){
        for(Playable obj : playlist)
            obj.info();
    }

    /**
     * DataSet calls this function when an event concerning the Playable objects occurred.
     * @param object The Data Object which is Playable that got operated on.
     * @param operation 0 for adding a data object, 1 for removing a data object from the observable.
     */
    public void update(DataObject object, int operation) {
        Playable playable = (Playable) object;

        if(operation == 0){
            playlist.add(playable);
            System.out.println("A new playable is added to the class " + this.toString() + ". Item info: ");
            playable.info();
        }

        else if(operation == 1){
            playlist.remove(playable);
            System.out.println("An item is removed from the playlist. Item info: ");
            playable.info();
        }

    }


}
