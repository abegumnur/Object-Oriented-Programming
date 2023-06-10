package BegumNur_src;

import BegumNur_interface.NonPlayable;
import BegumNur_interface.Visual;

import java.lang.String;

/**
 * @Author : Begum Nur
 * @Date : 05.06.2023
 * Represents an Image object.
 */
public class Image extends DataObject implements NonPlayable, Visual {

    /**
     * Stores the dimension information about the Image
     */
    private String dimensionInfo;

    /**
     * Constructor of the class.
     * @param name name of the image
     * @param dimensionInfo duration of the image
     * @param otherInfo other information about image
     */
    public Image(String name, String dimensionInfo, String otherInfo){
        super(name, otherInfo);
        this.dimensionInfo = dimensionInfo;
    }

    @Override
    public boolean isNonPlayable() {
        return true;
    }

    @Override
    public boolean isNonVisual() {
        return false;
    }

    @Override
    public boolean isPlayable() {
        return false;
    }

    @Override
    public boolean isVisual() {
        return true;
    }

    /**
     * Prints information about the Image to the terminal.
     */
    @Override
    public void info() {
        System.out.println("Image: " + getName() + ", Dimensions: " + dimensionInfo + ", Info: " + getOtherInfo());
    }

    /**
     * Imitates showing the Image by printing it to terminal.
     */
    @Override
    public void show(){
        System.out.println("Showing Image: " + getName() );

    }

}
