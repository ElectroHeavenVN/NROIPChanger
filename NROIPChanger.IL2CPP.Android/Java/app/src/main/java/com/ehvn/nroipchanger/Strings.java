package com.ehvn.nroipchanger;

public final class Strings {

    public static String fromFeature(String feature)
    {
        if (Utils.GetCurrentLanguage().equals("vi"))
        {
            switch (feature)
            {
                case "activate":
                    return "Kích hoạt";
                case "showNoti":
                    return "Hiện thông báo";
                case "newIPAddr":
                    return "Địa chỉ IP mới";
                case "newPort":
                    return "Cổng mới";
                case "hookAddr":
                    return "Địa chỉ hook";
                case "utf8CreateStringRVA":
                    return "RVA của System.String::CreateString(System.Byte* value, System.Int32 startIndex, System.Int32 length)";
                case "utf16CreateStringRVA":
                    return "RVA của System.String::CreateString(System.Char* value, System.Int32 startIndex, System.Int32 length)";
                case "tcpClientConnectRVA":
                    return "RVA của System.Net.Sockets.TcpClient::Connect(System.String hostname, System.Int32 port)";
                case "hookAddrNotice":
                    return "Sau khi thay đổi địa chỉ hook, bạn nên khởi động lại game để không gây ra lỗi.";
                case "settings":
                    return "Cài đặt";
                case "saveData":
                    return "Lưu dữ liệu";
                case "autoSize":
                    return "Tự động điều chỉnh kích thước theo chiều cao";
                case "close":
                    return "<font color='red'>Đóng</font>";
            }
        }
        return switch (feature) {
            case "activate" -> "Activate";
            case "showNoti" -> "Show notification";
            case "newIPAddr" -> "New IP address";
            case "newPort" -> "New port";
            case "hookAddr" -> "Hook addresses";
            case "utf8CreateStringRVA" ->
                    "RVA of System.String::CreateString(System.Byte* value, System.Int32 startIndex, System.Int32 length)";
            case "utf16CreateStringRVA" ->
                    "RVA of System.String::CreateString(System.Char* value, System.Int32 startIndex, System.Int32 length)";
            case "tcpClientConnectRVA" ->
                    "RVA of System.Net.Sockets.TcpClient::Connect(System.String hostname, System.Int32 port)";
            case "hookAddrNotice" -> "After changing hook addresses, you should restart the game to avoid crashes and errors.";
            case "settings" -> "Settings";
            case "saveData" -> "Save data";
            case "autoSize" -> "Auto size vertically";
            case "close" -> "<font color='red'>Close</font>";
            default -> feature;
        };
    }

    public static String hideOrKill()
    {
        if (Utils.GetCurrentLanguage().equals("vi"))
            return "Ẩn/đóng (giữ)";
        else
            return "Hide/close (Hold)";
    }

    public static String iconHidden()
    {
        if (Utils.GetCurrentLanguage().equals("vi"))
            return "Đã ẩn biểu tượng. Nhớ vị trí biểu tượng đã ẩn để mở lại.";
        else
            return "Icon hidden. Remember the hidden icon position.";
    }

    public static String menuKilled()
    {
        if (Utils.GetCurrentLanguage().equals("vi"))
            return "Đã đóng menu.";
        else
            return "Menu closed.";
    }

    public static String minimize()
    {
        if (Utils.GetCurrentLanguage().equals("vi"))
            return "Thu nhỏ";
        else
            return "Minimize";
    }

    public static String on()
    {
        if (Utils.GetCurrentLanguage().equals("vi"))
            return "Bật";
        else
            return "On";
    }

    public static String off()
    {
        if (Utils.GetCurrentLanguage().equals("vi"))
            return "Tắt";
        else
            return "Off";
    }

    public static String maxValue()
    {
        if (Utils.GetCurrentLanguage().equals("vi"))
            return "Giá trị tối đa";
        else
            return "Max value";
    }

    public static String inputNumber()
    {
        if (Utils.GetCurrentLanguage().equals("vi"))
            return "Nhập số";
        else
            return "Input number";
    }

    public static String ok()
    {
        return "OK";
    }

    public static String cancel()
    {
        if (Utils.GetCurrentLanguage().equals("vi"))
            return "Hủy";
        else
            return "Cancel";
    }

    public static String inputText()
    {
        if (Utils.GetCurrentLanguage().equals("vi"))
            return "Nhập nội dung";
        else
            return "Input text";
    }

    public static String gameCrashed()
    {
        if (Utils.GetCurrentLanguage().equals("vi"))
            return "Game bị văng đột ngột.";
        else
            return "Game has crashed unexpectedly.";
    }

    public static String logSavedTo()
    {
        if (Utils.GetCurrentLanguage().equals("vi"))
            return "Nhật ký đã được lưu tại";
        else
            return "Log saved to";
    }

    public static String overlayNotification()  //Will be called from native code
    {
        if (Utils.GetCurrentLanguage().equals("vi"))
            return "Cần quyền hiển thị trên các ứng dụng khác để hiển thị menu. Vui lòng bật nó.";
        else
            return "Overlay permission is required in order to show the menu. Please enable it.";
    }

    public static String gameLibNotLoaded() {
        if (Utils.GetCurrentLanguage().equals("vi"))
            return "Chức năng lưu cài đặt đã được bật. Đang chờ game tải thư viện vào bộ nhớ...\n\nBuộc tải menu có thể không áp dụng đổi IP ngay lập tức. Bạn cần phải kích hoạt lại đổi IP.";
        else
            return "Save preferences was been enabled. Waiting for game lib to be loaded...\n\nForce load menu may not apply IP change instantly. You would need to reapply IP change.";
    }

    public static String forceLoadMenu() {
        if (Utils.GetCurrentLanguage().equals("vi"))
            return "Buộc tải menu";
        else
            return "Force load menu";
    }

    public static String empty() {
        if (Utils.GetCurrentLanguage().equals("vi"))
            return "Trống";
        else
            return "Empty";
    }
}
