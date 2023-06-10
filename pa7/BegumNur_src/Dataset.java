package BegumNur_src;

import BegumNur_interface.IObserver;
import BegumNur_interface.NonPlayable;
import BegumNur_interface.Playable;

import java.util.ArrayList;

/**
 * @Author :Begum Nur
 * @Date : 05.06.2023
 * Represents the observable object in the Observer design.
 * Contains objects (Audio, Image, Text and Video) along with
 * observers (Players and Viewers).
 */

public class Dataset extends Observable{

    private ArrayList<DataObject> objects;
    private ArrayList<IObserver> observers;
    public Dataset(){
        observers = new ArrayList<>();
        objects = new ArrayList<>();
    }

    /**
     * Register an observer to the observer list.
     * @param observer Can be a Viewer or Player.
     */
    @Override
    public void register(IObserver observer) {
        observers.add(observer);
    }

    /**
     * Unregister an observer from the observer list.
     * @param observer The observer object to unregister
     */
    @Override
    public void unregister(IObserver observer) {
        observers.remove(observer);
    }

    /**
     * Notifies the appropriate observers when a change has been made in the Dataset.
     * Example: When a new Audio object is added to the objects list, all the registered Players gets notified.
     * @param object
     * @param operation
     */
    @Override
    public void notifyObservers(DataObject object, int operation) {
        for(var observer : observers){
            if(object instanceof Playable && observer instanceof Player){
                //System.out.println("Sending notify from dataset operation is 0");
                observer.update(object, operation);
            }
            else if(object instanceof NonPlayable && observer instanceof Viewer){
                //System.out.println("Sending notify from dataset operation is 1");
                observer.update(object, operation);
            }

        }

    }

    /**
     * Adds an object to the objects list.
     * @param object is the object to add
     * Operation is 0 for add.
     */
    @Override //also add this object to the every observers arraylist according to its superclass
    public void add(DataObject object) {
        objects.add(object);
        notifyObservers(object, 0);
    }

    /**,
     * Removes an object from the objects list.
     * @param object is the object to remove
     * Operation is 1 for remove.
     */
    @Override
    public void remove(DataObject object) {
        objects.remove(object);
        notifyObservers(object, 1);
    }

}
