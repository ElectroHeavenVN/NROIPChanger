.class Lcom/ehvn/nroipchanger/Main$1;
.super Ljava/lang/Object;

.implements Ljava/lang/Runnable;


.annotation system Ldalvik/annotation/EnclosingMethod;
    value = Lcom/ehvn/nroipchanger/Main;->ShowToastOnUIThread(Ljava/lang/String;I)V
.end annotation

.annotation system Ldalvik/annotation/InnerClass;
    accessFlags = 0x0
    name = null
.end annotation


.field final synthetic val$activity:Landroid/app/Activity;

.field final synthetic val$duration:I

.field final synthetic val$message:Ljava/lang/String;


.method constructor <init>(Landroid/app/Activity;Ljava/lang/String;I)V
    .locals 0
    .annotation system Ldalvik/annotation/Signature;
        value = {
            "()V"
        }
    .end annotation

    iput-object p1, p0, Lcom/ehvn/nroipchanger/Main$1;->val$activity:Landroid/app/Activity;

    iput-object p2, p0, Lcom/ehvn/nroipchanger/Main$1;->val$message:Ljava/lang/String;

    iput p3, p0, Lcom/ehvn/nroipchanger/Main$1;->val$duration:I

    invoke-direct {p0}, Ljava/lang/Object;-><init>()V

    return-void
.end method


.method public run()V
    .locals 3

    iget-object v0, p0, Lcom/ehvn/nroipchanger/Main$1;->val$activity:Landroid/app/Activity;

    iget-object v1, p0, Lcom/ehvn/nroipchanger/Main$1;->val$message:Ljava/lang/String;

    iget v2, p0, Lcom/ehvn/nroipchanger/Main$1;->val$duration:I

    invoke-static {v0, v1, v2}, Landroid/widget/Toast;->makeText(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;

    move-result-object v0

    invoke-virtual {v0}, Landroid/widget/Toast;->show()V

    return-void
.end method
