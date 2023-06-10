package BegumNur_src;

import BegumNur_interface.NonPlayable;
import BegumNur_interface.NonVisual;

import java.lang.String;

/**
 * @Author : Begum Nur
 * @Date : 05.06.2023
 * Represents a text object.
 */
public class Text extends DataObject implements NonVisual, NonPlayable
{
    public Text(String name, String otherInfo){
        super(name, otherInfo);

    }

    @Override
    public boolean isVisual() {
        return false;
    }

    @Override
    public boolean isPlayable() {
        return false;
    }

    @Override
    public boolean isNonPlayable() {return true;}

    @Override
    public boolean isNonVisual() {
        return true;
    }

    /**
     * Prints information about the Text to the terminal.
     */
    @Override
    public void info() {
        System.out.println("Info: " + getName() + ", Info: " + getOtherInfo());
    }


    /**
     * Imitates showing the Text by printing it to terminal.
     */
    @Override
    public void show() {
        System.out.println("Showing Text: " + getName());
    }
}
