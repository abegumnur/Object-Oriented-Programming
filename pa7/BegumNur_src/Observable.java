package BegumNur_src;

import BegumNur_interface.IObserver;

/**
 * @Author : Begum Nur
 * @Date : 05.06.2023
 * Represents an observable in the observer pattern.
 * DataSet is an observable class.
 */
public abstract class Observable {

    /**
     * Register the observer to the observable.
     * @param observer Observer to register.
     */
    abstract public void register(IObserver observer);

    /**
     * Unregister the observer from the observable class.
     * @param observer Observer to unregister.
     */
    abstract public void unregister(IObserver observer);

    /**
     * Notify the observers when a change occurs in the instance fields of the class.
     * Notify Player observers when a Playable is added/removed,
     * Notify Viewer observers when a NonPlayable is added/removed
     * @param object Data object of the dataset.
     * @param operation 0 for add, 1 for remove.
     */
    abstract public void notifyObservers(DataObject object, int operation);

    /**
     * Add the data object to the list of objects.
     * @param object object to add.
     */
    abstract public void add(DataObject object);

    /**
     * Remove the data object from the list of objects.
     * @param object object to remove.
     */
    abstract public void remove(DataObject object);

}

