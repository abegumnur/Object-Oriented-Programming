
package BegumNur_interface;

import BegumNur_src.DataObject;

/**
 * @Author : Begum Nur
 * @Date : 05.06.2023
 * Observer interface.
 */
public interface IObserver {
    /**
     * Update function gets called by the Observable object when a change has occurred in it.
     * @param object The Data Object that got operated on.
     * @param operation 0 for adding a data object, 1 for removing a data object from the observable.
     */
    void update(DataObject object, int operation);

}
