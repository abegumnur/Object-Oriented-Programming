package BegumNur_src;

import BegumNur_interface.IObserver;
import BegumNur_interface.NonPlayable;

import java.util.ArrayList;
import java.lang.IllegalAccessException;

/**
 * @Author : Begum Nur
 * @Date : 05.06.20230
 * Represent a type of observable in the observer pattern.
 * Viewer observers are interested in the changes that has been made to the NonPlayable objects only.
 */
public class Viewer implements IObserver {

    private ArrayList<NonPlayable> viewList;
    /**
     * Represents the index of the currently shown object.
     */
    private int current_index;

    public Viewer(){
        viewList = new ArrayList<>();
        current_index = 0;
    }

    /**
     * Shows the list of NonPlayable objects in the DataSet.
     */
    public void show_list(){
        for(NonPlayable vis : viewList)
            vis.info();
    }


    public NonPlayable currently_viewing(){
        return viewList.get(current_index);
    }

    /**
     * Skip to the next NonPlayable object.
     * @param type If text, skip to the closest next text object, if image skip to the closest next image object.
     * @exception IllegalAccessException if the viewlist is empty.
     */
    public void next(String type) throws IllegalAccessException {
        if(viewList.size() == 0)
            throw new IllegalAccessException("ViewList is empty. Cannot show the next item...\n");
            //System.out.println("ViewList is empty. Cannot show the next item...");

        if(type.equals("text")){
            for(int i = current_index + 1; i != viewList.size(); i++){
                if(viewList.get(i) instanceof Text){
                    current_index = i;
                    System.out.println("Showing the next item: ");
                    viewList.get(current_index).info();
                    //viewList.get(current_index).show();
                    break;
                }
            }
        }

        else if(type.equals("image")){
            for(int i = current_index + 1; i != viewList.size(); i++){
                if(viewList.get(i) instanceof Image){
                    current_index = i;
                    System.out.println("Showing the next item: ");
                    viewList.get(current_index).info();
                    //viewList.get(current_index).show();
                    break;
                }
            }
        }
/*
        else if(type.equals("nonplayable")){ // an item has been deleted
            for(int i = current_index ; i != viewList.size(); i++){

            }
        }
*/
    }

    /**
     * Skip to the previous NonPlayable object.
     * @param type If text, skip to the closest previous text object, if image skip to the closest previous image object.
     * @exception IllegalAccessException if the viewlist is empty.
     */
    public void previous(String type) throws IllegalAccessException {

        if(viewList.size() == 0)
            throw new IllegalAccessException("ViewList is empty. Cannot show the previous item.\n");
            //System.out.println("ViewList is empty. Cannot show the previous item...");


        if(type.equals("text")){
            for(int i = current_index - 1; i >= 0; i--){
                if(viewList.get(i) instanceof Text){
                    current_index = i;
                    viewList.get(current_index).show();
                    break;
                }
            }
        }

        else if(type.equals("image")){
            for(int i = current_index - 1; i >= 0; i--){
                if(viewList.get(i) instanceof Image){
                    current_index = i;
                    viewList.get(current_index).show();
                    break;
                }

            }
        }

    }

    /**
     * DataSet calls this function when an event concerning the NonPlayable objects occurred.
     * @param object The Data Object which is NonPlayable that got operated on.
     * @param operation 0 for adding a data object, 1 for removing a data object from the observable.
     */
    @Override
    public void update(DataObject object, int operation) {
        NonPlayable vis = (NonPlayable) object;
        if(operation == 0){
            viewList.add(vis);
            System.out.println("A new nonplayable is added to the class " + this.toString() + ". Item info: ");
            //object.info();
            vis.info();
        }
        else if(operation == 1){
            viewList.remove(vis);
            System.out.println("An nonplayable is removed from the playlist. Item info: ");
            vis.info();
            /*
            if(viewList.get(current_index).equals(object)){
                try
                {
                    next("nonplayable");
                }
                catch(IllegalAccessException il)
                {
                    System.out.println();
                }
            }*/

        }
    }
}
