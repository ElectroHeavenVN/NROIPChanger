package com.ehvn.nroipchanger;

import java.util.Dictionary;
import java.util.HashMap;

public final class Strings {

    static HashMap<String, String[]> features = new HashMap<String, String[]>();

    static boolean initialized = false;

    static void Initialize()
    {
        if (initialized)
            return;
        features.put("activate", new String[] {"Kích hoạt", "Activate"});
        features.put("showNoti", new String[] {"Hiện thông báo", "Show notification"});
        features.put("newIPAddr", new String[] {"Địa chỉ IP mới", "New IP address"});
        features.put("newPort", new String[] {"Cổng mới", "New port"});
        features.put("hookAddr", new String[] {"Địa chỉ hook", "Hook addresses"});
        features.put("utf8CreateStringRVA", new String[] {"RVA của System.String::CreateString(System.Byte* value, System.Int32 startIndex, System.Int32 length)", "RVA of System.String::CreateString(System.Byte* value, System.Int32 startIndex, System.Int32 length)"});
        features.put("utf16CreateStringRVA", new String[] {"RVA của System.String::CreateString(System.Char* value, System.Int32 startIndex, System.Int32 length)", "RVA of System.String::CreateString(System.Char* value, System.Int32 startIndex, System.Int32 length)"});
        features.put("tcpClientConnectRVA", new String[] {"RVA của System.Net.Sockets.TcpClient::Connect(System.String hostname, System.Int32 port)", "RVA of System.Net.Sockets.TcpClient::Connect(System.String hostname, System.Int32 port)"});
        features.put("hookAddrNotice", new String[] {"Sau khi thay đổi địa chỉ hook, bạn nên khởi động lại game để không gây ra lỗi.", "After changing hook addresses, you should restart the game to avoid crashes and errors."});
        features.put("settings", new String[] {"Cài đặt", "Settings"});
        features.put("saveData", new String[] {"Lưu dữ liệu", "Save data"});
        features.put("autoSize", new String[] {"Tự động điều chỉnh kích thước theo chiều cao", "Auto size vertically"});
        features.put("close", new String[] {"<font color='red'>Đóng</font>", "<font color='red'>Close</font>"});

        features.put("hideOrKill", new String[] {"Ẩn/đóng (giữ)", "Hide/close (Hold)"});
        features.put("iconHidden", new String[] {"Đã ẩn biểu tượng. Nhớ vị trí biểu tượng đã ẩn để mở lại.", "Icon hidden. Remember the hidden icon position."});
        features.put("menuKilled", new String[] {"Đã đóng menu.", "Menu closed."});
        features.put("minimize", new String[] {"Thu nhỏ", "Minimize"});
        features.put("on", new String[] {"Bật", "On"});
        features.put("off", new String[] {"Tắt", "Off"});
        features.put("maxValue", new String[] {"Giá trị tối đa", "Max value"});
        features.put("inputNumber", new String[] {"Nhập số", "Input number"});
        features.put("ok", new String[] {"OK", "OK"});
        features.put("cancel", new String[] {"Hủy", "Cancel"});
        features.put("inputText", new String[] {"Nhập nội dung", "Input text"});
        features.put("gameCrashed", new String[] {"Game bị văng đột ngột.", "Game has crashed unexpectedly."});
        features.put("logSavedTo", new String[] {"Nhật ký đã được lưu tại", "Log saved to"});
        features.put("overlayNotification", new String[] {"Cần quyền hiển thị trên các ứng dụng khác để hiển thị menu. Vui lòng bật nó.", "Overlay permission is required in order to show the menu. Please enable it."});
        features.put("gameLibNotLoaded", new String[] {"Chức năng lưu cài đặt đã được bật. Đang chờ game tải thư viện vào bộ nhớ...\n\nBuộc tải menu có thể không áp dụng đổi địa chỉ máy chủ ngay lập tức. Bạn cần phải kích hoạt lại đổi máy chủ.", "Save preferences was been enabled. Waiting for game lib to be loaded...\n\nForce load menu may not apply server change instantly. You would need to reapply server change."});
        features.put("forceLoadMenu", new String[] {"Buộc tải menu", "Force load menu"});
        features.put("empty", new String[] {"Trống", "Empty"});

        features.put("installFromOtherSourcesWarning", new String[] {"Không cài từ các nguồn không rõ!", "Do not install from other sources!"});
        features.put("defaultIPAddress", new String[] {"Địa chỉ máy chủ mặc định", "Default server address"});
        features.put("defaultRVAs", new String[] {"RVA mặc định", "Default RVAs"});

        initialized = true;
    }

    public static String fromFeature(String feature)
    {
        Initialize();
        if (features.get(feature) == null)
            return feature;
        if (Utils.GetCurrentLanguage().equals("vi"))
            return features.get(feature)[0];
        else
            return features.get(feature)[1];
    }

    public static String hideOrKill()
    {
        return fromFeature("hideOrKill");
    }

    public static String iconHidden()
    {
        return fromFeature("iconHidden");
    }

    public static String menuKilled()
    {
        return fromFeature("menuKilled");
    }

    public static String minimize()
    {
        return fromFeature("minimize");
    }

    public static String on()
    {
        return fromFeature("on");
    }

    public static String off()
    {
        return fromFeature("off");
    }

    public static String maxValue()
    {
        return fromFeature("maxValue");
    }

    public static String inputNumber()
    {
        return fromFeature("inputNumber");
    }

    public static String ok()
    {
        return fromFeature("ok");
    }

    public static String cancel()
    {
        return fromFeature("cancel");
    }

    public static String inputText()
    {
        return fromFeature("inputText");
    }

    public static String gameCrashed()
    {
        return fromFeature("gameCrashed");
    }

    public static String logSavedTo()
    {
        return fromFeature("logSavedTo");
    }

    public static String overlayNotification()  //Will be called from native code
    {
        return fromFeature("overlayNotification");
    }

    public static String gameLibNotLoaded() 
    {
        return fromFeature("gameLibNotLoaded");
    }

    public static String forceLoadMenu() 
    {
        return fromFeature("forceLoadMenu");
    }

    public static String empty() 
    {
        return fromFeature("empty");
    }

    public static String defaultIPAddress()
    {
        return fromFeature("defaultIPAddress");
    }

    public static String defaultRVAs()
    {
        return fromFeature("defaultRVAs");
    }

    public static String installFromOtherSourcesWarning()
    {
        return fromFeature("installFromOtherSourcesWarning");
    }
}