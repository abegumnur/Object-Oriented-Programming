package BegumNur_src;

import BegumNur_interface.NonVisual;
import BegumNur_interface.Playable;

import java.lang.String;
/**
 * @Author : Begum Nur
 * @Date : 05.06.2023
 *  Represents Audio object.
*/

public class Audio extends DataObject implements Playable, NonVisual
{
    /**
     * Duration information of the Audio object.
     */
    private String duration;

    /**
     * Constructor of the class.
     * @param name name of the audio
     * @param duration duration of the audio
     * @param otherInfo other information about audio
     */
    public Audio(String name, String duration, String otherInfo){
        super(name, otherInfo);
        this.duration = duration;

    }

    @Override
    public boolean isVisual() {
        return false;
    }

    @Override
    public boolean isPlayable() {
        return true;
    }

    @Override
    public boolean isNonVisual() {
        return true;
    }

    @Override
    public boolean isNonPlayable() {
        return false;
    }

    /**
     * Prints information about the Audio to the terminal.
     */
    @Override
    public void info() {
        System.out.println("Audio: " + getName() + ", Duration: " + duration + ", Info: " + getOtherInfo());
    }

    /**
     * Imitates playing the Audio by printing it to terminal.
     */
    @Override
    public void play() {
        System.out.println("Playing audio: " + getName());
    }
}
