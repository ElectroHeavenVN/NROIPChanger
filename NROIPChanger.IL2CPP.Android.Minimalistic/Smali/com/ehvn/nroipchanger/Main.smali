.class public Lcom/ehvn/nroipchanger/Main;
.super Ljava/lang/Object;

.field public static mainActivity:Landroid/content/Context;


.method static constructor <clinit>()V
    .locals 1

    const-string v0, "NROIPChanger"

    invoke-static {v0}, Ljava/lang/System;->loadLibrary(Ljava/lang/String;)V

    return-void
.end method

.method public constructor <init>()V
    .locals 0

    invoke-direct {p0}, Ljava/lang/Object;-><init>()V

    return-void
.end method

.method private static native Init(Landroid/content/Context;)V
.end method

.method public static ShowToastOnUIThread(Ljava/lang/String;I)V
    .locals 2

    sget-object v0, Lcom/ehvn/nroipchanger/Main;->mainActivity:Landroid/content/Context;

    if-nez v0, :cond_0

    return-void

    :cond_0
    check-cast v0, Landroid/app/Activity;

    new-instance v1, Lcom/ehvn/nroipchanger/Main$1;

    invoke-direct {v1, v0, p0, p1}, Lcom/ehvn/nroipchanger/Main$1;-><init>(Landroid/app/Activity;Ljava/lang/String;I)V

    invoke-virtual {v0, v1}, Landroid/app/Activity;->runOnUiThread(Ljava/lang/Runnable;)V

    return-void
.end method

.method public static Start(Landroid/content/Context;)V
    .locals 0

    sput-object p0, Lcom/ehvn/nroipchanger/Main;->mainActivity:Landroid/content/Context;

    invoke-static {p0}, Lcom/ehvn/nroipchanger/Main;->Init(Landroid/content/Context;)V

    return-void
.end method
