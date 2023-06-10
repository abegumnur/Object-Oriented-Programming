package BegumNur_src;

import BegumNur_interface.Playable;
import BegumNur_interface.Visual;

import java.lang.String;

/**
 * @Author : Begum Nur
 * @Date : 05.06.2023
 * Represents a Video object.
 */
public class Video extends DataObject implements Playable, Visual
{
    private String duration;

    /**
     * Constructor of the class.
     * @param name name of the video
     * @param duration duration of the video
     * @param otherInfo other information about video
     */
    public Video(String name, String duration, String otherInfo){
        super(name,otherInfo);
        this.duration = duration;
    }

    @Override
    public boolean isNonPlayable() {
        return false;
    }

    @Override
    public boolean isNonVisual() {
        return false;
    }

    @Override
    public boolean isPlayable() {
        return true;
    }

    @Override
    public boolean isVisual() {
        return true;
    }

    /**
     * Prints information about the Video to the terminal.
     */
    @Override
    public void info() {
            System.out.println("Video: " + getName() + ", Duration: " + duration + ", Info: " + getOtherInfo());
    }

    /**
     * Imitates playing the Video by printing it to terminal.
     */
    @Override
    public void play() {
        System.out.println("Playing Video: " + getName());
    }

}
