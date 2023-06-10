package BegumNur_src;

import java.lang.String;

/**
 * @Author : Begum Nur
 * @Date : 05.06.2023
 * Base class for Audio, Text, Video and Image classes.
 * Since all of them contains name and other info fields.
 * Along with Playable-Visual categorization.
 */
public abstract class DataObject {
    private String name;
    private String otherInfo;

    public DataObject(String name, String otherInfo){
        this.name = name;
        this.otherInfo = otherInfo;

    }
    protected String getName(){
        return name;
    }
    protected String getOtherInfo(){
        return otherInfo;
    }

    public abstract boolean isPlayable();
    public abstract boolean isNonPlayable();
    public abstract boolean  isVisual();
    public abstract boolean isNonVisual();

}
