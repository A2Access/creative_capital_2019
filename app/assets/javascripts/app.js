webpackJsonp([1],{EjdU:function(t,e){},LkaG:function(t,e){},NHnr:function(t,e,a){"use strict";Object.defineProperty(e,"__esModule",{value:!0});var n=a("7+uW"),r=a("JkCx"),i=a.n(r),s=void 0,o={data:function(){return{imageUrl:window.floorPlanPath}},mounted:function(){var t=this;(s=i.a.create({container:this.$refs.heatmap})).setData({max:5,data:[]}),setInterval(function(){t.$store.dispatch("fetchCurrent")},4e3)},computed:{dataPoints:function(){return s&&s.setData({max:35,data:this.$store.getters.newDataPoints}),this.$store.getters.newDataPoints}}},u={render:function(){var t=this.$createElement,e=this._self._c||t;return e("div",{ref:"heatmap",attrs:{id:"map"}},[e("img",{attrs:{src:this.imageUrl}}),this._v(" "),e("div",{directives:[{name:"show",rawName:"v-show",value:!0,expression:"1 == 1"}]},[this._v("\n    "+this._s(this.dataPoints)+"\n  ")])])},staticRenderFns:[]};var c={name:"App",components:{appMap:a("VU/8")(o,u,!1,function(t){a("LkaG")},"data-v-47b00b4f",null).exports}},p={render:function(){var t=this.$createElement,e=this._self._c||t;return e("div",{attrs:{id:"app"}},[e("app-map")],1)},staticRenderFns:[]};var d=a("VU/8")(c,p,!1,function(t){a("EjdU")},null,null).exports,l=a("mvHQ"),f=a.n(l),m=a("NYxO"),h=a("7t+N"),v=a.n(h);n.a.use(m.a);var w=new m.a.Store({strict:!0,state:{heatmap:null,nodes:[]},mutations:{updateNodes:function(t,e){t.nodes=e}},actions:{fetchCurrent:function(t,e){var a=t.commit;v.a.ajax({type:"POST",url:"/graphql",contentType:"application/json",dataType:"json",data:f()({query:"{ current { id title temperature x y } }"})}).done(function(t){a("updateNodes",t.data.current)}).fail(function(){console.log("fetch failed")})}},getters:{newDataPoints:function(t){return t.nodes.map(function(t){return{id:t.id,value:t.temperature,x:t.x*v()("#map").width(),y:t.y*v()("#map").height(),radius:200,title:t.title}})}}});n.a.config.productionTip=!1,new n.a({store:w,el:"#app",components:{App:d},template:"<App/>"})}},["NHnr"]);
//# sourceMappingURL=app.js.map