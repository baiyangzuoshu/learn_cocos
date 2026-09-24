const {ccclass, property} = cc._decorator;

@ccclass
export default class Helloworld extends cc.Component {

    private _loggedFrames: number = 0;

    @property(cc.Label)
    label: cc.Label = null;

    @property
    text: string = 'hello';

    private trace (phase: string) {
        const scene = cc.director.getScene();
        const sceneName = scene ? scene.name : 'none';
        cc.log(`[Lifecycle] scene=${sceneName} node=${this.node.name} frame=${cc.director.getTotalFrames()} ${phase}`);
    }

    onLoad () {
        this.trace('onLoad');
    }

    onEnable () {
        this.trace('onEnable');
    }

    start () {
        this.trace('start');
        this.label.string = this.text;
    }

    update () {
        if (this._loggedFrames < 3) this.trace('update');
    }

    lateUpdate () {
        if (this._loggedFrames < 3) {
            this.trace('lateUpdate');
            this._loggedFrames++;
        }
    }

    onDisable () {
        this.trace('onDisable');
    }

    onDestroy () {
        this.trace('onDestroy');
    }
}
