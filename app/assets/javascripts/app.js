webpackJsonp([1],{EjdU:function(t,e){},NHnr:function(t,e,n){"use strict";Object.defineProperty(e,"__esModule",{value:!0});var a=n("7+uW"),r=n("JkCx"),i=n.n(r),s=void 0,o={data:function(){return{imageUrl:window.floorPlanPath}},mounted:function(){var t=this;(s=i.a.create({container:this.$refs.heatmap})).setData({max:5,data:[{x:250,y:250,value:30,radius:200}]}),setInterval(function(){t.$store.dispatch("fetchCurrent")},4e3)},computed:{dataPoints:function(){return s&&s.setData({min:22,max:27,data:this.$store.getters.newDataPoints}),this.$store.getters.newDataPoints}}},u={render:function(){var t=this.$createElement,e=this._self._c||t;return e("div",{ref:"heatmap",attrs:{id:"map"}},[e("img",{attrs:{src:this.imageUrl}}),this._v(" "),e("div",{directives:[{name:"show",rawName:"v-show",value:!0,expression:"1 == 1"}]},[this._v("\n    "+this._s(this.dataPoints)+"\n  ")])])},staticRenderFns:[]};var c={name:"App",components:{appMap:n("VU/8")(o,u,!1,function(t){n("WSsB")},"data-v-332f571f",null).exports}},p={render:function(){var t=this.$createElement,e=this._self._c||t;return e("div",{attrs:{id:"app"}},[e("app-map")],1)},staticRenderFns:[]};var d=n("VU/8")(c,p,!1,function(t){n("EjdU")},null,null).exports,l=n("mvHQ"),f=n.n(l),m=n("NYxO"),h=n("7t+N"),v=n.n(h);a.a.use(m.a);var x=new m.a.Store({strict:!0,state:{heatmap:null,nodes:[]},mutations:{updateNodes:function(t,e){t.nodes=e}},actions:{fetchCurrent:function(t,e){var n=t.commit;v.a.ajax({type:"POST",url:"/graphql",contentType:"application/json",dataType:"json",data:f()({query:"{ current { id title temperature x y } }"})}).done(function(t){n("updateNodes",t.data.current)}).fail(function(){console.log("fetch failed")})}},getters:{newDataPoints:function(t){return t.nodes.map(function(t){return{id:t.id,value:t.temperature,x:t.x,y:t.y,radius:200,title:t.title}})}}});a.a.config.productionTip=!1,new a.a({store:x,el:"#app",components:{App:d},template:"<App/>"})},WSsB:function(t,e){}},["NHnr"]);
//# sourceMappingURL=app.js.map