
(cl:in-package :asdf)

(defsystem "robotics_project-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :nav_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "customOdom" :depends-on ("_package_customOdom"))
    (:file "_package_customOdom" :depends-on ("_package"))
    (:file "floatStamped" :depends-on ("_package_floatStamped"))
    (:file "_package_floatStamped" :depends-on ("_package"))
  ))