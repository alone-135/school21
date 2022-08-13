import{d as f,i as x,a as L,b as T,c as _,m as C,u as v,e as O,j as I,r as c,l as k,K as y,g as N,f as K,R as b,h as A,k as P,I as R,n as F,o as M}from"./vendor.6cea80fb.js";const D=function(){const s=document.createElement("link").relList;if(s&&s.supports&&s.supports("modulepreload"))return;for(const t of document.querySelectorAll('link[rel="modulepreload"]'))r(t);new MutationObserver(t=>{for(const a of t)if(a.type==="childList")for(const i of a.addedNodes)i.tagName==="LINK"&&i.rel==="modulepreload"&&r(i)}).observe(document,{childList:!0,subtree:!0});function o(t){const a={};return t.integrity&&(a.integrity=t.integrity),t.referrerpolicy&&(a.referrerPolicy=t.referrerpolicy),t.crossorigin==="use-credentials"?a.credentials="include":t.crossorigin==="anonymous"?a.credentials="omit":a.credentials="same-origin",a}function r(t){if(t.ep)return;t.ep=!0;const a=o(t);fetch(t.href,a)}};D();f.extend(x);f.extend(L);f.extend(T);f.extend(_);f.extend(C);f.extend(v);f.extend(O);f.updateLocale("en",{weekStart:1});const Y="modulepreload",w={},$="/",j=function(s,o){return!o||o.length===0?s():Promise.all(o.map(r=>{if(r=`${$}${r}`,r in w)return;w[r]=!0;const t=r.endsWith(".css"),a=t?'[rel="stylesheet"]':"";if(document.querySelector(`link[href="${r}"]${a}`))return;const i=document.createElement("link");if(i.rel=t?"stylesheet":Y,t||(i.as="script",i.crossOrigin=""),i.href=r,document.head.appendChild(i),t)return new Promise((l,n)=>{i.addEventListener("load",l),i.addEventListener("error",()=>n(new Error(`Unable to preload CSS for ${r}`)))})})).then(()=>s())},u=I.exports.jsx,re=I.exports.jsxs,ne=I.exports.Fragment,S=()=>u("svg",{className:"spinner",viewBox:"0 0 50 50",children:u("circle",{className:"path",cx:"25",cy:"25",r:"20",fill:"none",strokeWidth:"5"})});var g=(e=>(e.eventFeedbackTimerStarted="eventFeedbackTimerStarted",e.checkAliveKey="checkAliveKey",e.ignoredEventsForFeedback="ignoredEventsForFeedback",e.authTime="authTime",e))(g||{}),p=(e=>(e.SET_ITEM="front localStorage setItem",e.GET_ITEM="front localStorage getItem",e.REMOVE_ITEM="front localStorage removeItem",e))(p||{});const U=(e,s,o=window)=>{const r=c.exports.useRef();c.exports.useEffect(()=>{r.current=s},[s]),c.exports.useEffect(()=>{if(!(o==null?void 0:o.addEventListener))return;const a=i=>r.current&&r.current(i);return o.addEventListener(e,a),()=>{o.removeEventListener(e,a)}},[e,r,o])};function V(e,s,o){try{localStorage.setItem(e,s)}catch(r){o&&o(p.SET_ITEM,r.toString())}}function B(e,s){var r;let o="";try{o=(r=localStorage.getItem(e))!=null?r:""}catch(t){s&&s(p.GET_ITEM,t.toString())}return o}function J(e,s){try{localStorage.removeItem(e)}catch(o){s&&s(p.REMOVE_ITEM,o.toString())}}const m={setItem:V,getItem:B,removeItem:J};function se(e,s){const o=c.exports.useCallback(n=>{m.setItem(e,k.exports.isObject(n)&&!k.exports.isNull(n)?JSON.stringify(n):String(n))},[e]),[r,t]=c.exports.useState(()=>{const n=m.getItem(e);try{return n?JSON.parse(n):(s&&o(s),s)}catch{return n}}),a=c.exports.useCallback(n=>{const d=n instanceof Function?n(r):n;o(d),t(d)},[o,r]),i=c.exports.useCallback(()=>{m.removeItem(e),t(null)},[e]),l=c.exports.useCallback(n=>{if(n.storageArea===localStorage&&n.key===e&&n.oldValue!==n.newValue)if(n.newValue===null)t(null);else try{const d=JSON.parse(n.newValue);t(d)}catch{t(n.newValue)}},[e]);return U("storage",l),[r,a,i]}const q=e=>{document.cookie=`tokenId=${e}; path=/`},H=()=>{document.cookie="tokenId=; path=/; max-age=0"},E=e=>{q(e)},ae=()=>{H()},W="/services/rest/auth-support/check-authenticated-user",z=()=>window.SUPPORT_DOMAIN&&window.SUPPORT_DOMAIN===window.location.host?"/auth/":window.KEYCLOAK_ENDPOINT&&window.KEYCLOAK_ENDPOINT!=="${KEYCLOAK_ENDPOINT}"?window.KEYCLOAK_ENDPOINT:`${void 0}/auth/`,G=()=>window.KEYCLOAK_CLIENT&&window.KEYCLOAK_CLIENT!=="${KEYCLOAK_CLIENT}"?window.KEYCLOAK_CLIENT:"",h=y({realm:"EduPowerKeycloak",url:z(),clientId:G()}),Q=({children:e})=>{const[s,o]=c.exports.useState(!1),r=c.exports.useCallback(()=>!s,[s]),t=c.exports.useCallback(i=>{const{token:l}=i;l&&(E(l),o(!0))},[o]),a=c.exports.useCallback(i=>{if(i==="onAuthSuccess"){const l=h.tokenParsed,n=N(l,"auth_time"),d=m.getItem(g.authTime);n&&n.toString()!==d&&(m.setItem(g.authTime,n),m.setItem(g.ignoredEventsForFeedback,JSON.stringify([])),m.setItem(g.eventFeedbackTimerStarted,""),h.token&&E(h.token),K.create().get(W,{params:{returnTo:window.location.origin,errorLogoutRedirect:window.location.origin}}))}},[]);return u(b,{isLoadingCheck:r,LoadingComponent:u(S,{}),initOptions:{onLoad:"login-required",checkLoginIframe:!1},authClient:h,onTokens:t,onEvent:a,children:e})},X=A(()=>j(()=>import("./index.2d90397a.js").then(function(e){return e.eY}),["index.2d90397a.js","vendor.6cea80fb.js"]),{fallback:u(S,{})}),Z=()=>u(Q,{children:u(X,{})}),ee=window.location.hostname==="localhost";ee||P({dsn:window.SENTRY_DSN,integrations:[new R.BrowserTracing],tracesSampleRate:1,environment:window.location.host,release:window.PRODUCT_VERSION||"local"});const te={gtmId:window.GTM_ID,events:{clickNotifications:"click_notifications"}};F.initialize(te);M.render(u(Z,{}),document.getElementById("root"));export{ne as F,S as L,g as S,j as _,re as a,ae as c,ee as i,u as j,m as s,se as u};